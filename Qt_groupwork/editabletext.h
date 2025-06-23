#ifndef EDITABLETEXT_H
#define EDITABLETEXT_H

#include "mygraphicsobject.h"

class EditableText : public MyGraphicsObject
{
public:
    EditableText();
    int type() const override;
};

#endif // EDITABLETEXT_H
