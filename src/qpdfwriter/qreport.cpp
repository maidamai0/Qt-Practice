#include "qreport.h"
#include "qdir.h"
#include "qpagesize.h"

#include <QDateTime>
#include <QFile>
#include <QPainter>
#include <QPdfWriter>
#include <QTextOption>

namespace {
constexpr auto page_margin = 100;
constexpr auto page_width = 2479;
constexpr auto page_resolution = 300;
} // namespace

void QReport::MakePDFReport() {
  QString full_file_path = "report.pdf";
  QFile pdf_file(full_file_path);
  pdf_file.open(QIODevice::WriteOnly);
  auto* pdf_writer = new QPdfWriter(&pdf_file);
  pdf_writer->setPageSize(QPageSize(QPageSize::A4));
  pdf_writer->setResolution(page_resolution); // pixel 3508*2479
  pdf_writer->setTitle("Report");

  pdf_writer->setPageMargins(QMarginsF(page_margin, page_margin, page_margin, page_margin));

  QDateTime currentTime = QDateTime::currentDateTime();
  QString timeString = currentTime.toString("yyyy-MM-dd hh:mm:ss ddd");

  auto* pdfPainter = new QPainter(pdf_writer);

  QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
  option.setWrapMode(QTextOption::WordWrap);
  int yCurrentP = 0;
  int xCurrentP = 0;
  int contentWidth = page_width - page_margin;

  QFont font;
  font.family();
  //    font.setFamily("simsun.ttc");
  font.setFamily("Times New Roman");
  int fontSize = 9;
  int textHeight = 90;
  font.setPointSize(fontSize);
  pdfPainter->setFont(font);

  QPixmap titleImage;
  titleImage.load("smile.png");
  pdfPainter->drawPixmap(xCurrentP, yCurrentP, titleImage.width() / 2, titleImage.height() / 2, titleImage);

  option.setAlignment(Qt::AlignRight | Qt::AlignBottom);
  int pageIndex = 1;
  int totalPageIndex = 2;
  QString pageIndexString = QString::number(pageIndex) + "/" + QString::number(totalPageIndex);
  pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth, titleImage.height() / 2), pageIndexString, option);

  yCurrentP += (titleImage.height() / 2 + 4);
  QPen pen;
  int penHeigth = 4;
  pen.setWidth(penHeigth);
  pen.setColor(Qt::blue);
  pdfPainter->setPen(pen);
  pdfPainter->drawLine(xCurrentP, yCurrentP, contentWidth, yCurrentP);

  pen.setColor(Qt::black);
  pdfPainter->setPen(pen);
  yCurrentP += penHeigth;

  yCurrentP += 100;

  fontSize = 22;
  font.setPointSize(fontSize);
  pdfPainter->setFont(font);
  option.setAlignment(Qt::AlignCenter);
  pdfPainter->drawText(QRect(0, yCurrentP, contentWidth, textHeight), QString("analysis report"), option);

  yCurrentP += (textHeight + 100);
  fontSize = 16;
  font.setPointSize(fontSize);
  pdfPainter->setFont(font);
  option.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth, 80), QString("channel droplet distribution map"));

  yCurrentP += (80 + 100);
  xCurrentP += 200;
  option.setWrapMode(QTextOption::WordWrap);
  pdfPainter->drawText(
    QRect(xCurrentP, yCurrentP, contentWidth - xCurrentP, 400),
    QString("ROX channel profile, FAM channel profile, HEX channel profile, CY5 channel profile. ROX channel profile, "
            "FAM channel profile, HEX channel profile, CY5 channel profile. ROX channel profile, FAM channel "
            "Distribution map, HEX channel distribution map, CY5 channel distribution map."),
    option);

  yCurrentP += (400 + 100);
  std::string imageFileName = "ROX.bmp";
  QPixmap roxImage = QPixmap(QString::fromStdString(imageFileName));
  pdfPainter->drawPixmap(0, yCurrentP, roxImage.width() / 2, roxImage.height() / 2, roxImage);
  //    pdfPainter->scale(1, 1);

  std::string famFileName = "FAM.bmp";
  QPixmap famImage = QPixmap(QString::fromStdString(famFileName));
  pdfPainter->drawPixmap(contentWidth / 2, yCurrentP, famImage.width() / 2, famImage.height() / 2, famImage);

  yCurrentP += (std::max(roxImage.height(), famImage.height()) + 100);

  xCurrentP = 0;
  pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth - xCurrentP, 80), QString("cross analysis result"),
                       option);

  std::string logo = "smile.png";
  QPixmap logoImage;
  logoImage.load(QString::fromStdString(logo));

  yCurrentP = 3508 - page_margin - (logoImage.height() / 2) + 4;
  pen.setColor(Qt::blue);
  pdfPainter->setPen(pen);
  pdfPainter->drawLine(0, yCurrentP, contentWidth, yCurrentP);
  yCurrentP = 3508 - page_margin - (logoImage.height() / 2);
  option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
  fontSize = 9;
  font.setPointSize(fontSize);
  pen.setColor(Qt::black);
  pdfPainter->setPen(pen);
  pdfPainter->drawPixmap(contentWidth - xCurrentP - logoImage.width() / 2, yCurrentP, logoImage.width() / 2,
                         logoImage.height() / 2, logoImage);
  pdfPainter->setFont(font);
  pdfPainter->drawText(QRect(0, yCurrentP, 600, logoImage.height()), timeString, option);

  delete pdfPainter;
  delete pdf_writer;
  pdf_file.close();
}
