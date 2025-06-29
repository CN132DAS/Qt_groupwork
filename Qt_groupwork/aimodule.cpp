#include "aimodule.h"

AImodule::AImodule(QWidget *parent)
    : QWidget{parent},networkManager(new QNetworkAccessManager(this)),
    mode(TreeMode),modeChanged(false)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("AI Module");
    QIcon WindowIcon(":/assets/WindowIcon.png");
    setWindowIcon(WindowIcon);
    this->resize(500,700);

    mainLayout = new QVBoxLayout(this);
    text1 = new QLabel("输入",this);
    mainLayout->addWidget(text1);
    inputTextEdit = new QTextEdit("chat with deepseek!",this);
    mainLayout->addWidget(inputTextEdit);
    text2 = new QLabel("输出",this);
    mainLayout->addWidget(text2);
    output = new QStackedWidget(this);
    mainLayout->addWidget(output);
    buttonLayout = new QHBoxLayout(this);

    clear_PB = new QPushButton("清除输出",this);
    commit_PB = new QPushButton("发送",this);
    modeSwitch_PB = new QPushButton("切换模式",this);

    connect(clear_PB,&QPushButton::clicked,
            this,&AImodule::toggle_clear_PB);
    connect(commit_PB,&QPushButton::clicked,
            this,&AImodule::toggle_commit_PB);
    connect(modeSwitch_PB,&QPushButton::clicked,
            this,&AImodule::toggle_modeSwitch_PB);
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &AImodule::apiReplyFinished);

    buttonLayout->addWidget(clear_PB);
    buttonLayout->addWidget(commit_PB);
    buttonLayout->addWidget(modeSwitch_PB);
    mainLayout->addLayout(buttonLayout);

    outputTextEdit = new QTextEdit(output);
    outputTextEdit->setReadOnly(true);
    treeWidget = new QTreeWidget(output);
    treeWidget->setHeaderLabel("Tree Structure");
    output->addWidget(treeWidget);
    output->addWidget(outputTextEdit);
}

void AImodule::show_ui(){
    if(mode == TreeMode)
        this->show_treeMode();
    else
        this->show_chatMode();
    this->show();
}

//private
void AImodule::show_treeMode(){
    setWindowTitle("AI Module --节点图模式");
    output->setCurrentIndex(0);
}

void AImodule::show_chatMode(){
    setWindowTitle("AI Module --对话模式");
    output->setCurrentIndex(1);
}

//override
void AImodule::closeEvent(QCloseEvent *event){
    this->hide();
    emit this->close();
    event->ignore();
}

//slot
void AImodule::toggle_clear_PB(){
    outputTextEdit->clear();
    treeWidget->clear();
}

void AImodule::toggle_commit_PB(){
    QString originalInput = inputTextEdit->toPlainText().trimmed();
    if (originalInput.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入内容！");
        return;
    }
    QString hint;
    if(mode == TreeMode)
        hint ="我需要生成一个思维导图，思维导图的形式是树 ，有至少两个层级,请务必严格按照以下格式输出：按照顺序依次输出各个节点,在每个节点前用#的数量来表示层级.例如：#根节点\n##父节点1\n###子节点1-1\n###子节点1-2\n##父节点2\n###子节点2-1\n####子子节点2-1-1\n且务必千万不要输出任何其他内容!以下为思维导图的生成提示：\"";
    else
        hint ="请对我用双引号括出来的内容进行解释，注意不要在答案中出现任何如“你”或“我”这种指代用户和你的词，以下是需要你解释的词\"";
    QString userInput = hint + originalInput +"\"";
    // DeepSeek API 请求URL（请替换为实际的API地址）
    QString apiUrl = "https://api.deepseek.com/v1/chat/completions";
    // 构造请求头
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer sk-d329c8fed0e344958e1e634e05470dce"); 
    // 构造请求体（JSON格式）
    QJsonObject requestBody;
    requestBody["model"] = "deepseek-chat";
    requestBody["messages"] = QJsonArray{
        QJsonObject{
            {"role", "user"},
            {"content", userInput}
        }
    };
    QJsonDocument doc(requestBody);
    QByteArray data = doc.toJson();
    // 发送POST请求
    networkManager->post(request, data);
}

void AImodule::toggle_modeSwitch_PB(){
    if(mode==TreeMode){
        mode = ChatMode;
        this->show_chatMode();
    }
    else if(mode == ChatMode){
        mode = TreeMode;
        this->show_treeMode();
    }
    output->currentWidget()->show();
    output->update();
}

void AImodule::apiReplyFinished(QNetworkReply *reply){
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "错误", "API请求失败: " + reply->errorString());
        reply->deleteLater();
        return;
    }
    // 读取API返回的JSON数据
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();
    // 提取DeepSeek的回复（假设API返回格式为 {"choices": [{"message": {"content": "..."}}]}）
    QString replyText = jsonObj["choices"].toArray()[0].toObject()["message"].toObject()["content"].toString();
    // 在输出框中显示回复
    if(mode==TreeMode){
        QStringList parts = replyText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        int prev_jing = 0;
        QTreeWidgetItem *curr_Item = nullptr;

        for(QString q : parts) {
            int num_jing = 0;
            while(!q.isEmpty() && q[0] == '#') {
                num_jing++;
                q.remove(0, 1);
            }

            if(q.isEmpty() || num_jing == 0) continue;
            if(num_jing > prev_jing + 1) {
                qDebug() << "Invalid level jump from" << prev_jing << "to" << num_jing;
                continue;
            }
            if(num_jing <= prev_jing) {
                int steps_back = prev_jing - num_jing + 1;
                while (steps_back-- > 0 && curr_Item) {
                    curr_Item = curr_Item->parent();
                }
            }

            QTreeWidgetItem *newItem = new QTreeWidgetItem();
            newItem->setText(0, q);
            newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);

            if(num_jing == 1) {
                treeWidget->addTopLevelItem(newItem);
            } else {
                if(curr_Item) curr_Item->addChild(newItem);
            }

            curr_Item = newItem;
            prev_jing = num_jing;
        }
        treeWidget->expandAll();
    }
    else        
        outputTextEdit->append("DeepSeek: " + replyText);
    reply->deleteLater();
}
