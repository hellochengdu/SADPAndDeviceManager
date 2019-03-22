#include "ExcelBase.h"
#include <QFile>
#include <QDir>
#include "QMessageBox"
#include <QList>
#include <QDebug>
#if defined(Q_OS_WIN)
#include <ActiveQt/QAxObject>
#endif // Q_OS_WIN

#include <qt_windows.h>


#define TC_FREE(x)  {delete x; x=NULL;}

class ExcelBasePrivate
{
	Q_DECLARE_PUBLIC(ExcelBase)
public:
	explicit ExcelBasePrivate(ExcelBase* qptr);
	~ExcelBasePrivate();

	void construct();
	void destory();

	ExcelBase* const q_ptr;

#if defined(Q_OS_WIN)
	QAxObject*  excel;
	QAxObject*  books;
	QAxObject*  book;
	QAxObject*  sheets;
	QAxObject*  sheet;
#endif
	QString     filename;
	QString     sheetName;
};

ExcelBasePrivate::ExcelBasePrivate(ExcelBase *qptr)
	: q_ptr(qptr)
#if defined(Q_OS_WIN)
	, excel(NULL)
	, books(NULL)
	, book(NULL)
	, sheets(NULL)
	, sheet(NULL)
#endif // Q_OS_WIN
{
}

ExcelBasePrivate::~ExcelBasePrivate()
{
#if defined(Q_OS_WIN)
	if (excel)
	{
		if (!excel->isNull())
		{
			excel->dynamicCall("Quit()");
		}
	}
	TC_FREE(sheet);
	TC_FREE(sheets);
	TC_FREE(book);
	TC_FREE(books);
	TC_FREE(excel);
#endif // Q_OS_WIN
}

void ExcelBasePrivate::construct()
{
#if defined(Q_OS_WIN)
	destory();
	excel = new QAxObject("Excel.Application", q_ptr);
//	excel->setControl("Excel.Application");

	if (!excel->isNull())
	{
		excel->setProperty("Visible", false);
		excel->setProperty("DisplayAlerts", false);
	}
	if (excel->isNull())
	{
		excel->setControl("ET.Application");
	}
	if (!excel->isNull())
	{
		books = excel->querySubObject("Workbooks");
	}

#endif // Q_OS_WIN
}

void ExcelBasePrivate::destory()
{
#if defined(Q_OS_WIN)
	TC_FREE(sheet);
	TC_FREE(sheets);
	if (book != NULL && !book->isNull())
	{
		//book->dynamicCall("Close(Boolean)", false);
		book->dynamicCall("Close()");//�رչ�����
	}
	TC_FREE(book);
	TC_FREE(books);
	if (excel != NULL && !excel->isNull())
	{
		excel->dynamicCall("Quit()");
	}
	TC_FREE(excel);
	filename = "";
	sheetName = "";
#endif // Q_OS_WIN
}


ExcelBase::ExcelBase(QObject* par) :QObject(par)
, d_ptr(new ExcelBasePrivate(this))
{
	HRESULT r = OleInitialize(0);
	if (r != S_OK && r != S_FALSE)
	{
		QMessageBox::warning(NULL, "��ʾ", "fail", QMessageBox::Ok);
	}
}

ExcelBase::~ExcelBase()
{
	close();
	delete d_ptr;
	OleUninitialize();
}

bool ExcelBase::create(const QString& filename)
{
	bool ret = false;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	d->construct();
	if (d->books != NULL && !d->books->isNull())
	{
		d->books->dynamicCall("Add");
		d->book = d->excel->querySubObject("ActiveWorkBook");
		d->sheets = d->book->querySubObject("WorkSheets");
		currentSheet();
		d->filename = filename;
		ret = true;
	}
#else
	Q_UNUSED(filename)
#endif // Q_OS_WIN
		return ret;
}

bool ExcelBase::open(const QString& filename)
{
	bool ret = false;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	d->construct();
	if (d->books != NULL && !d->books->isNull())
	{
		d->books->dynamicCall("Open (const QString&)", filename);
		d->book = d->excel->querySubObject("ActiveWorkBook");

		ret = d->book != NULL && !d->book->isNull();
		if (ret)
		{
			d->sheets = d->book->querySubObject("WorkSheets");
			d->filename = filename;
			currentSheet();
		}
	}
#else
	Q_UNUSED(filename)
#endif // Q_OS_WIN
		return ret;
}

void ExcelBase::saveAs(const QString& filename)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->book != NULL && !d->book->isNull())
	{
		d->filename = filename;
		QString strPath = d->filename;
		strPath = strPath.replace('/', '\\');
		qDebug() << strPath;
	//	d->book->dynamicCall("SaveAs(const QString&,int,const QString&,const QString&,bool,bool)", strPath
		//	, 56, QString(""), QString(""), false, false);

		d->book->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(strPath));
	}
#else
	Q_UNUSED(filename)
#endif // Q_OS_WIN
}
///
/// \brief ����excel
///
void ExcelBase::save()
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->filename.isEmpty())
		return;
	saveAs(d->filename);
#else
	Q_UNUSED(filename)
#endif // Q_OS_WIN
}

void ExcelBase::close()
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	d->destory();
#endif // Q_OS_WIN
}

void ExcelBase::kick()
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);

	if (d->excel != NULL && !d->excel->isNull())
	{
		d->excel->setProperty("Visible", true);
	}
	TC_FREE(d->sheet);
	TC_FREE(d->sheets);
	TC_FREE(d->book);
	TC_FREE(d->books);
	TC_FREE(d->excel);
	d->destory();
#endif // Q_OS_WIN
}

QStringList ExcelBase::sheetNames()
{
	QStringList ret;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheets != NULL && !d->sheets->isNull())
	{
		int sheetCount = d->sheets->property("Count").toInt();
		for (int i = 1; i <= sheetCount; i++)
		{
			QAxObject* sheet = d->sheets->querySubObject("Item(int)", i);
			if (NULL == sheet || sheet->isNull())
				continue;
			ret.append(sheet->property("Name").toString());
			delete sheet;
		}
	}
#endif // Q_OS_WIN
	return ret;
}

QString ExcelBase::currentSheetName()
{
	Q_D(ExcelBase);
	return d->sheetName;
}

void ExcelBase::setVisible(bool value)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->excel != NULL && !d->excel->isNull())
	{
		d->excel->setProperty("Visible", value);
	}
#else
	Q_UNUSED(value)
#endif // Q_OS_WIN
}

void ExcelBase::setCaption(const QString& value)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->excel != NULL && !d->excel->isNull())
	{
		d->excel->setProperty("Caption", value);
	}
#else
	Q_UNUSED(value)
#endif // Q_OS_WIN
}

bool ExcelBase::addBook()
{
	bool ret = false;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->excel != NULL && !d->excel->isNull())
	{
		TC_FREE(d->sheet);
		TC_FREE(d->sheets);
		TC_FREE(d->book);
		TC_FREE(d->books);
		d->books = d->excel->querySubObject("WorkBooks");
		ret = d->books != NULL && !d->books->isNull();
	}
#endif // Q_OS_WIN
	return ret;
}

bool ExcelBase::currentSheet()
{
	bool ret = false;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	TC_FREE(d->sheet);
	if (d->excel != NULL && !d->excel->isNull())
	{
		TC_FREE(d->sheet);
		d->sheet = d->excel->querySubObject("ActiveWorkBook");
		ret = d->sheet != NULL && !d->sheet->isNull();
		d->sheetName = ret ? d->sheet->property("Name").toString() : "";
	}
#endif // Q_OS_WIN
	return ret;
}

bool ExcelBase::setCurrentSheet(int index)
{
	bool ret = false;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheets != NULL && !d->sheets->isNull())
	{
		TC_FREE(d->sheet);
		d->sheet = d->sheets->querySubObject("Item(int)", index);
		ret = d->sheet != NULL && !d->sheet->isNull();
		if (ret)
		{
			d->sheet->dynamicCall("Activate(void)");
		}
		d->sheetName = ret ? d->sheet->property("Name").toString() : "";

		sheetRowStart = d->sheet->querySubObject("UsedRange")->querySubObject("Rows")->property("Row").toInt();
		sheetColumnStart = d->sheet->querySubObject("UsedRange")->querySubObject("Columns")->property("Column").toInt();
	}
#else
	Q_UNUSED(index)
#endif // Q_OS_WIN
		return ret;
}

int ExcelBase::sheetCount()
{
	int ret = 0;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheets != NULL && !d->sheets->isNull())
	{
		ret = d->sheets->property("Count").toInt();
	}
#endif // Q_OS_WIN
	return ret;
}

void ExcelBase::cellFormat(int row, int col, const QString& format)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
		range->setProperty("NumberFormatLocal", format);
		delete range;
	}
#else
	Q_UNUSED(row)
		Q_UNUSED(col)
		Q_UNUSED(format)
#endif // Q_OS_WIN
}

void ExcelBase::cellAlign(int row, int col, Alignment hAlign, Alignment vAlign)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
		range->setProperty("HorizontalAlignment", hAlign);
		range->setProperty("VerticalAlignment", vAlign);
		delete range;
	}
#else
	Q_UNUSED(row)
		Q_UNUSED(col)
		Q_UNUSED(hAlign)
		Q_UNUSED(vAlign)
#endif // Q_OS_WIN
}

QVariant ExcelBase::read(int row, int col)
{
	QVariant ret;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
		//ret = range->property("Value");
		ret = range->dynamicCall("Value()");
		delete range;
	}
#else
	Q_UNUSED(row)
		Q_UNUSED(col)
#endif // Q_OS_WIN
		return ret;
}

void ExcelBase::write(int row, int col, const QVariant& value)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject* range = d->sheet->querySubObject("Cells(int, int)", row, col);
		range->setProperty("Value", value);
		delete range;
	}
#else
	Q_UNUSED(row)
		Q_UNUSED(col)
		Q_UNUSED(value)
#endif // Q_OS_WIN
}

bool ExcelBase::usedRange(int& rowStart, int& colStart, int& rowEnd, int& colEnd)
{
	bool ret = false;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject* urange = d->sheet->querySubObject("UsedRange");
		rowStart = urange->property("Row").toInt();
		colStart = urange->property("Column").toInt();
		rowEnd = urange->querySubObject("Rows")->property("Count").toInt();
		colEnd = urange->querySubObject("Columns")->property("Count").toInt();
		delete urange;
		ret = true;
	}
#else
	Q_UNUSED(rowStart)
		Q_UNUSED(colStart)
		Q_UNUSED(rowEnd)
		Q_UNUSED(colEnd)
#endif // Q_OS_WIN
		return ret;
}
///
/// \brief ��ȡ����sheet
/// \return
///
QVariant ExcelBase::readAll()
{
	QVariant var;
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *usedRange = d->sheet->querySubObject("UsedRange");
		if (NULL == usedRange || usedRange->isNull())
		{
			return var;
		}
		var = usedRange->dynamicCall("Value");
		delete usedRange;
	}
#endif
	return var;
}
///
/// \brief ��ȡ����sheet�����ݣ������õ�cells��
/// \param cells
///
void ExcelBase::readAll(QList<QList<QVariant> > &cells)
{
#if defined(Q_OS_WIN)
	castVariant2ListListVariant(readAll(), cells);
#else
	Q_UNUSED(cells);
#endif

}

///
/// \brief д��һ���������
/// \param cells
/// \return �ɹ�д�뷵��true
/// \see readAllSheet
///
bool ExcelBase::writeCurrentSheet(const QList<QList<QVariant> > &cells)
{
#if defined(Q_OS_WIN)
	Q_D(ExcelBase);
	if (cells.size() <= 0)
		return false;
	if (NULL == d->sheet || d->sheet->isNull())
		return false;
	int row = cells.size();
	int col = cells.at(0).size();
	QString rangStr;
	convertToColName(col, rangStr);
	rangStr += QString::number(row);
	rangStr = "A1:" + rangStr;
	qDebug() << rangStr;
	QAxObject *range = d->sheet->querySubObject("Range(const QString&)", rangStr);
	if (NULL == range || range->isNull())
	{
		return false;
	}
	bool succ = false;
	QVariant var;
	castListListVariant2Variant(cells, var);
	succ = range->setProperty("Value", var);
	delete range;
	return succ;
#else
	return true;
#endif
}
///
/// \brief ������ת��Ϊexcel����ĸ�к�
/// \param data ����0����
/// \return ��ĸ�кţ���1->A 26->Z 27 AA
///
void ExcelBase::convertToColName(int data, QString &res)
{
	//Q_ASSERT(data > 0 && data < 65535);
	int tempData = data / 26;
	if (tempData > 0 && !(data % 26))
	{
		tempData = 0;
	}

	if (tempData > 0)
	{
		int mode = data % 26;
		convertToColName(mode, res);
		convertToColName(tempData, res);
	}
	else
	{
		res = (to26AlphabetString(data) + res);
	}
}
///
/// \brief ����ת��Ϊ26��ĸ
///
/// 1->A 26->Z
/// \param data
/// \return
///
QString ExcelBase::to26AlphabetString(int data)
{
	QChar ch;//A��Ӧ0x41
	if (!data)
	{
		//ch = data + 0x41;
	}
	else
	{
		ch = data + 0x40;
	}

	return QString(ch);
}
///
/// \brief QList<QList<QVariant> >ת��ΪQVariant
/// \param cells
/// \return
///
void ExcelBase::castListListVariant2Variant(const QList<QList<QVariant> > &cells, QVariant &res)
{
	QVariantList vars;
	const int rows = cells.size();
	for (int i = 0; i < rows; ++i)
	{
		vars.append(QVariant(cells[i]));
	}
	res = QVariant(vars);
}
///
/// \brief ��QVariantתΪQList<QList<QVariant> >
/// \param var
/// \param res
///
void ExcelBase::castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
	QVariantList varRows = var.toList();
	if (varRows.isEmpty())
	{
		return;
	}
	const int rowCount = varRows.size();
	QVariantList rowData;
	for (int i = 0; i < rowCount; ++i)
	{
		rowData = varRows[i].toList();
		res.push_back(rowData);
	}
}

void ExcelBase::SetFreezeSelCell(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column - 1);
		range->dynamicCall("Select()");
		d->excel->querySubObject("ActiveWindow")->setProperty("FreezePanes", "True");
		delete range;
	}
}
void ExcelBase::setFitHeight(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		bool aa = range->setProperty("WrapText", true);
		delete range;
	}
}
void ExcelBase::setFontSize(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		/*QString cell;
		cell.append(QChar(sheetColumnStart + column - 1 + 'A'));
		cell.append(QString::number(sheetRowStart + row));*/

		//QAxObject *range = d->sheet->querySubObject("Range(const QString&)", cell);
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		range = range->querySubObject("Font");
		range->setProperty("Size", 9);
		range->setProperty("Name", QStringLiteral("����"));
		delete range;
	}
}

void ExcelBase::setRowHeight(int row, int height)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QString rowsName;
		rowsName.append(QString::number(sheetRowStart + row));
		rowsName.append(":");
		rowsName.append(QString::number(sheetRowStart + row));

		QAxObject * range = d->sheet->querySubObject("Rows(const QString &)", rowsName);
		range->setProperty("RowHeight", height);
		delete range;
	}
}
void ExcelBase::setBorder(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Borders");
		bool  aa=range->setProperty("xlDiagonalDown", "xlNone");
		delete range;
	}
}

void ExcelBase::setCellBorder(int row, int column, const QString& borderPos, const QString& lineStyle, const QString colorStyle, const QString& tintAndShade, const QString& weight)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		range = range->querySubObject("Borders");
		range->dynamicCall("Borders(const QString&)", borderPos);
		range->setProperty("LineStyle", lineStyle);
		range->setProperty("ThemeColor", colorStyle);
		range->setProperty("TintAndShade", tintAndShade);
		range->setProperty("Weight", weight);
		delete range;
	}
}

void ExcelBase::setColumnWidth(int column, int width)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QString columnName;
		columnName.append(QChar(sheetColumnStart + column - 1 + 'A'));
		columnName.append(":");
		columnName.append(QChar(sheetColumnStart + column - 1 + 'A'));

		QAxObject * col = d->sheet->querySubObject("Columns(const QString&)", columnName);
		col->setProperty("ColumnWidth", width);

		delete col;
	}
}

void ExcelBase::setCellFontBold(int row, int column, bool isBold)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QString cell;
		cell.append(QChar(sheetColumnStart + column - 1 + 'A'));
		cell.append(QString::number(sheetRowStart + row));

		QAxObject *range =d->sheet->querySubObject("Range(const QString&)", cell);
		range = range->querySubObject("Font");
		range->setProperty("Bold", isBold);

		delete range;
	}
}

void ExcelBase::setCellString(int row, int column, const QString& value)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		range->dynamicCall("SetValue(const QString&)", value);

		delete range;
	}
}

void ExcelBase::setCellTextCenter(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QString cell;
		cell.append(QChar(sheetColumnStart + column - 1 + 'A'));
		cell.append(QString::number(sheetRowStart + row));

		QAxObject *range = d->sheet->querySubObject("Range(const QString&)", cell);
		range->setProperty("HorizontalAlignment", xlCenter);//xlCenter    
		delete range;
	}
}

void ExcelBase::unlockCell(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		range->setProperty("Locked", false);

		delete range;
	}
}

void ExcelBase::lockSheet(int iIndex)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		d->sheet = d->sheets->querySubObject("Item(int)", iIndex);
		d->sheet->dynamicCall("Protect", true);
	}
}

void ExcelBase::setCellFormat(int row, int column, const QString& format)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		range->setProperty("NumberFormatLocal", format);

		delete range;
	}
}

void ExcelBase::mergeCells(int topLeftRow, int topLeftColumn, int bottomRightRow, int bottomRightColumn)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QString cell;
		cell.append(QChar(topLeftColumn - 1 + 'A'));
		cell.append(QString::number(sheetRowStart + topLeftRow));
		cell.append(":");
		cell.append(QChar(bottomRightColumn - 1 + 'A'));
		cell.append(QString::number(sheetRowStart + bottomRightRow));

		QAxObject *range = d->sheet->querySubObject("Range(const QString&)", cell);
		range->setProperty("VerticalAlignment", -4108);//xlCenter    
		range->setProperty("WrapText", true);
		range->setProperty("MergeCells", true);

		delete range;
	}
}

void ExcelBase::setScienceMethod(int row, int column)
{
	Q_D(ExcelBase);
	if (d->sheet != NULL && !d->sheet->isNull())
	{
		QAxObject *range = d->sheet->querySubObject("Cells(int,int)", sheetRowStart + row, sheetColumnStart + column);
		range->setProperty("NumberFormatLocal", "@");
		delete range;
	}
}
