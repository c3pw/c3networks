#ifndef MACVALIDATOR_H
#define MACVALIDATOR_H

#include <QObject>
#include <QValidator>

class MacValidator : public QValidator
    {
    public:
        MacValidator();

        // QValidator interface
    public:
        State validate(QString &text, int &number) const override;
    };

#endif // MACVALIDATOR_H
