#ifndef NUMBERTOWORDS_H
#define NUMBERTOWORDS_H

#include <QVector>
#include "stdio.h"

class NumberToWords
{
public:
  NumberToWords();
  QString doubleToWords ( double );

  ~NumberToWords();

private:
  QString defineNumber (int&, int, int, const QString& );
  QString integerToWords ( int );
};

#endif // NUMBERTOWORDS_H
