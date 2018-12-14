#include "numbertowords.h"

#include <QtDebug>

QVector<std::string> const names [ ] = {{"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve",
                                     "diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisite", "dieciocho", "diecinueve" },
                                    {"-", "-", "veinte--", "treinta--", "cuarenta--", "cincuenta--", "sesenta--", "setenta--", "ochenta--", "noventa--"}
                                   };
NumberToWords::NumberToWords( )
{

}

QString NumberToWords::doubleToWords ( double number )
{
  // convert double number to words
  QString nbr = QString::number(number, 'f', 2);
  QRegExp rx("(\\.)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
  QStringList numbers = nbr.split(rx);

  return integerToWords(numbers.at(0).toInt()) + " con " + numbers.at(1) + "/100";
}

QString NumberToWords::defineNumber ( int &count, int unit, int xx, const QString &units )
{
  QString nbrWords = "";

  int         div     = unit * (xx == 0 ? 1 : 10);
  int         index   = count / div;
  int         sub     = index * div * (index >= 2 ? 1 : 0);
  std::string name    = names[xx][index];

  if (name[name.size()-1] == '-') {
    name.erase(name.size()-1);
    index   = (count-sub)/unit;
    name.append(names[0][index]);
  }
  if (name != "") {
    nbrWords = QString::fromStdString(name) +  units;
      //qDebug() << nbrWords;
  }
  count   = count - (count/unit*unit);

  return nbrWords;
}

QString NumberToWords::integerToWords(int number)
{
  QString nbrWords = "";

  if (number == 0) {
     nbrWords = "Cero";
  }
  nbrWords = defineNumber(number, 1000000, 0, "millones ");
  nbrWords = nbrWords + defineNumber(number, 100000,  0, "cientos ");
  nbrWords = nbrWords + defineNumber(number, 1000,    1, "mil ");
  nbrWords = nbrWords + defineNumber(number, 100,     0, "cientos ");
  nbrWords = nbrWords + defineNumber(number, 1,       1, "");

  nbrWords.replace("unocientos", "ciento");
  nbrWords.replace("cincocientos", "quinientos");
  nbrWords.replace("sietecientos", "setecientos");
  nbrWords.replace("nuevecientos", "novecientos");
  nbrWords.replace("unomil", "unmil");

  if ( nbrWords[nbrWords.size()-1] == "-")
    nbrWords.replace("-", "");

  nbrWords.replace("-", " y ");

  nbrWords.replace(0, 1, nbrWords[0].toUpper());

  return nbrWords;
}
