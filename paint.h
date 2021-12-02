#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QPen>
#include <QMouseEvent>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QFileDialog>
#include <QPainter>
#include <QToolTip>
#include <QColorDialog>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class paint; }
QT_END_NAMESPACE

class paint : public QMainWindow
{
    Q_OBJECT

public:
    paint(QWidget *parent = nullptr);
    ~paint();

private:
    Ui::paint *ui;
    QCursor drawing_cursor;
    QCursor btns_cursor;

    QImage image;

    QColor color;
    QColor pen_color;
    QColor eraser_color;
    QPen pen;
    QBrush brush;

    QList<QPoint> list;

    QString file_name;

    //Start and end points
    QPoint one;
    QPoint two;

    bool is_pressed;

    bool draw_pen;
    bool draw_eraser;
    bool draw_line;
    bool draw_rectangle;
    bool draw_ellipse;
    bool draw_color_beam;

    void cursor(int);
    void draw_tool(bool,bool,bool,bool,bool,bool);

public slots:
    void slot_pen_1();
    void slot_rubber_2();
    void slot_line_3();
    void slot_rectangle_4();
    void slot_elipse_5();
    void slot_color_beam_6();

    void slot_black();
    void slot_white();
    void slot_green();
    void slot_blue();
    void slot_orange();
    void slot_red();
    void set_color();

    void set_size(int);
    void slot_save();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
};
#endif // PAINT_H
