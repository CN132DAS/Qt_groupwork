#include "picturecontent.h"
#include "function.h"

QPen PictureContent::selectedPen = QPen(Qt::red, 3, Qt::DashLine);
//public
PictureContent::PictureContent(QString name_,int ID_,QString suffix_,bool loadMode):
    MyGraphicsObject(),ID(ID_),suffix(suffix_) {
    if(loadMode)
        copy_file_to_temp(name_);
    picture = QPixmap(get_fileTempPath(name_));
    width = picture.width();
    height = picture.height();
}

void PictureContent::save(QTextStream& out,int& i){
    if(!deleted){
        QPointF pos = this->scenePos();
        QString oldName = "Pic_"+QString::number(ID)+"."+suffix;
        QString newName = "Pic_"+QString::number(i)+"."+suffix;
        out<<i<<" "<<newName<<" "<<pos.x()<<" "<<pos.y()<<Qt::endl;
        QFile::copy(get_fileTempPath(oldName),get_filePath(newName));
        ID = i;
        i++;
    }
}

//override
QString PictureContent::get_info() const{return "pic "+QString::number(this->ID);}

void PictureContent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);
    if (option->state & QStyle::State_Selected) {
        painter->save();
        painter->setPen(selectedPen);
        painter->drawRect(boundingRect().adjusted(-2, -2, 2, 2));
        painter->restore();
    }
    painter->drawPixmap(-width / 2, -height / 2, picture);
}

QRectF PictureContent::boundingRect() const{
    return QRectF(-width / 2, -height / 2, width, height);
}

int PictureContent::type() const{
    return UserType + 1;
}

void PictureContent::open(){
    QDesktopServices::openUrl(QUrl::fromLocalFile(get_fileTempPath("Pic_"+QString::number(ID)+"."+suffix)));
}
