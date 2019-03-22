#pragma once


#include <QObject>
#include <ActiveQt/QAxObject>
#include <QString>
#include <QStringList>
#include <QVariant>

class ExcelBasePrivate;
///
/// \brief win��excel���ٶ�ȡ��
/// �ο������ĿԴ�룬���Դ���ַ��https://github.com/qtcn/tianchi/blob/v0.0.2-build20130701/include/tianchi/file/tcmsexcel.h
///
class ExcelBase : public QObject
{
public:
	ExcelBase(QObject* par = NULL);
	~ExcelBase();
private:
	Q_DISABLE_COPY(ExcelBase)
		Q_DECLARE_PRIVATE(ExcelBase)
		ExcelBasePrivate* const d_ptr;
public:
	/// @brief ���÷���ĳ���
	enum Alignment
	{
		xlTop = -4160, ///< ����
		xlLeft = -4131, ///< ����
		xlRight = -4152, ///< ����
		xlCenter = -4108, ///< ����
		xlBottom = -4107  ///< ����
	};

	/// @brief ����һ��Microsoft Excel�ļ�
	bool create(const QString& filename = QString());
	/// @brief ��һ��Microsoft Excel�ļ�
	bool open(const QString& filename = QString());
	/// @brief ���Microsoft Excel�ļ�
	void saveAs(const QString& filename);
	void save();
	/// @brief �ر�Microsoft Excel�ļ�
	void close();
	/// @brief �߳���ǰ�򿪵� Microsoft Excel<br>
	/// @brief �����˶���Ը� Excel �Ŀ���Ȩ<br>
	/// @brief Excel �ļ��Ա��ִ򿪣���ɥʧ�˿���Ȩ
	void kick();

	/// @brief ���õ�ǰ�򿪵� Excel �Ƿ�ɼ�
	void setVisible(bool value);
	/// @brief ���� Excel �ĵ��ı���
	void setCaption(const QString& value);

	/// @brief �½�һ�� Excel �ĵ�
	bool addBook();

	/// @brief ���ص�ǰ Excel �� Sheet ����
	int sheetCount();

	/// @brief ���ص�ǰ�򿪵� Excel ȫ�� Sheet ��
	QStringList sheetNames();

	/// @brief ���ص�ǰ Sheet.
	bool currentSheet();

	/// @brief ���ò�ָ����ǰ Sheet.
	/// @param [in] ��ǰ Sheet �������� 1 ��ʼ
	bool setCurrentSheet(int index);

	/// @brief ��ǰ�򿪵� Excel �� Sheet ��
	QString currentSheetName();

	/// @brief ��ȡ��Ԫ�� Sheet ������
	/// @param [in] row �кţ��� 1 ��ʼ
	/// @param [in] col �кţ��� 1 ��ʼ
	/// @return ����ָ����Ԫ�������
	QVariant read(int row, int col);

	/// @brief ��ȡ��Ԫ�� Sheet ������
	/// @param [in] row �кţ��� 1 ��ʼ
	/// @param [in] col �кţ��� 1 ��ʼ
	/// @return ����ָ����Ԫ�������
	inline QVariant cell(int row, int col) { return read(row, col); }

	/// @brief д�뵥Ԫ�� Sheet ������
	/// @param [in] row �кţ��� 1 ��ʼ
	/// @param [in] col �кţ��� 1 ��ʼ
	/// @param [in] value ׼��д�������
	void write(int row, int col, const QVariant& value);

	void cellFormat(int row, int col, const QString& format);
	void cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);

	/// @brief ��ȡ��Ч������Ϣ
	/// @see rowStart() const
	/// @see rowEnd() const
	/// @see colStart() const
	/// @see colEnd() const
	bool usedRange(int& rowStart, int& colStart, int &rowEnd, int &colEnd);

	QVariant readAll();
	void readAll(QList<QList<QVariant> > &cells);
	bool writeCurrentSheet(const QList<QList<QVariant> > &cells);

	static void convertToColName(int data, QString &res);
	static QString to26AlphabetString(int data);
	static void castListListVariant2Variant(const QList<QList<QVariant> > &cells, QVariant& res);
	static void castVariant2ListListVariant(const QVariant& var, QList<QList<QVariant> > &res);

	//add 2017/10/24 ----crs

	int sheetRowStart;
	int sheetColumnStart;

	//������Ԫ��
	void SetFreezeSelCell(int row, int column);
	//�����и�
	void setRowHeight(int row, int height);
	//���õ�Ԫ��߿� 
	void setCellBorder(int row, int column, const QString& borderPos, const QString& lineStyle, const QString colorStyle, const QString& tintAndShade, const QString& weight);
	//�����п� 
	void setColumnWidth(int column, int width);
	//���õ�Ԫ�����
	void setCellFontBold(int row, int column, bool isBold);
	//���õ�Ԫ��stringֵ
	void setCellString(int row, int column, const QString& value);
	//���õ�Ԫ���ı�����
	void setCellTextCenter(int row, int column);
	
	//������Ԫ��
	void unlockCell(int row, int column);
	//������
	void lockSheet(int iIndex);

	void setCellFormat(int row, int column, const QString& format);
	//��Ԫ���ں�
	void mergeCells(int topLeftRow, int topLeftColumn, int bottomRightRow, int bottomRightColumn);
	//�Զ����У�����Ӧ�߶�
	void setFitHeight(int row, int column);
	//���������С
	void setFontSize(int row, int column);
	//���ñ߿�
	void setBorder(int row, int column);
	//�����ı����ܾ���ѧ���㷨��
	void setScienceMethod(int row, int column);
};