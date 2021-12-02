#include "paint.h"
#include "ui_paint.h"
paint::paint(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::paint)
{
    ui->setupUi(this);

   QCursor cursor_btn = QCursor(Qt::PointingHandCursor);
    ui->black_button->setCursor(cursor_btn);
    ui->blue_button->setCursor(cursor_btn);
    ui->line_button->setCursor(cursor_btn);
    ui->eraser_button->setCursor(cursor_btn);
    ui->green_button->setCursor(cursor_btn);
    ui->orange_button->setCursor(cursor_btn);
    ui->palette_button->setCursor(cursor_btn);
    ui->pen_button->setCursor(cursor_btn);
    ui->white_button->setCursor(cursor_btn);
    ui->red_button->setCursor(cursor_btn);
    ui->save_button->setCursor(cursor_btn);
    ui->rectangle_button->setCursor(cursor_btn);
    ui->ellipse_button->setCursor(cursor_btn);
    ui->pen_slider->setCursor(cursor_btn);
    ui->color_beam_button->setCursor(cursor_btn);

    connect(ui->pen_button,SIGNAL(clicked(bool)),SLOT(slot_pen_1()));
    connect(ui->eraser_button,SIGNAL(clicked(bool)),SLOT(slot_rubber_2()));
    connect(ui->line_button,SIGNAL(clicked(bool)),SLOT(slot_line_3()));
    connect(ui->rectangle_button,SIGNAL(clicked(bool)),SLOT(slot_rectangle_4()));
    connect(ui->ellipse_button,SIGNAL(clicked(bool)),SLOT(slot_elipse_5()));
    connect(ui->color_beam_button,SIGNAL(clicked(bool)),SLOT(slot_color_beam_6()));

    connect(ui->black_button,SIGNAL(clicked(bool)),SLOT(slot_black()));
    connect(ui->blue_button,SIGNAL(clicked(bool)),SLOT(slot_blue()));
    connect(ui->green_button,SIGNAL(clicked(bool)),SLOT(slot_green()));
    connect(ui->orange_button,SIGNAL(clicked(bool)),SLOT(slot_orange()));
    connect(ui->white_button,SIGNAL(clicked(bool)),SLOT(slot_white()));
    connect(ui->red_button,SIGNAL(clicked(bool)),SLOT(slot_red()));
    connect(ui->palette_button,SIGNAL(clicked(bool)),SLOT(set_color()));

    connect(ui->pen_slider,SIGNAL(valueChanged(int)),SLOT(set_size(int)));

    connect(ui->save_button,SIGNAL(clicked(bool)),SLOT(slot_save()));


    ui->paper_label->setFrameStyle(QFrame::StyledPanel);
    cursor(1);
    draw_tool(1,0,0,0,0,0);

    QImage image_2(1042,532,QImage::Format_RGB32);
    image = image_2;
    image.fill(Qt::white);
    ui->paper_label->setPixmap(QPixmap::fromImage(image));

    pen_color = Qt::black;
    eraser_color= Qt::white;
    pen.setColor(pen_color);
}

paint::~paint()
{
    delete ui;
}


void paint::draw_tool(bool pen,bool rubber,
                      bool line,bool rectangle ,
                      bool ellipse , bool color_beam)
{
        draw_pen = pen;
        draw_eraser = rubber;
        draw_line = line;
        draw_rectangle = rectangle;
        draw_ellipse = ellipse;
        draw_color_beam = color_beam;
}

void paint::cursor(int a)
{
    switch(a)
    {
       case 1 :
        drawing_cursor = QCursor(QPixmap(":/tools/pen_cursor.png"));
        ui->paper_label->setCursor(drawing_cursor);
          break;
       case 2 :
        drawing_cursor = QCursor(QPixmap(":/tools/eraser_cursor.png"));
        ui->paper_label->setCursor(drawing_cursor);
          break;
       case 3 :
        drawing_cursor = QCursor(QPixmap(":/tools/cross_cursor.png"));
        ui->paper_label->setCursor(drawing_cursor);
       break;
       default :
        drawing_cursor = QCursor(QPixmap(":/tools/pen_cursor.png"));
        ui->paper_label->setCursor(drawing_cursor);
   }
}

void paint::slot_save()
{
    file_name = QFileDialog::getSaveFileName(this,
                                             "Saving",
                                             "/my_work.png",
                                             "Images (*.png *.jpg *.xpm)"
                                             );
    if (file_name.isEmpty())
        return;
    image.save(file_name);
}


void paint::slot_black()
{
    if(draw_color_beam)
        return;
    if(draw_eraser)
    {
        eraser_color=Qt::black;
        ui->eraser_color_lbl->setStyleSheet("background-color:black");
    }
    else
    {
        pen_color=Qt::black;
        ui->pen_color_lbl->setStyleSheet("background-color:black");
    }
    pen.setColor(Qt::black);
}

void paint::slot_blue()
{
    if(draw_color_beam)
        return;
    if(draw_eraser)
    {
       eraser_color=Qt::blue;
       ui->eraser_color_lbl->setStyleSheet("background-color:blue");
    }
    else
    {
       pen_color=Qt::blue;
       ui->pen_color_lbl->setStyleSheet("background-color:blue");
    }
    pen.setColor(Qt::blue);
}

void paint::slot_green()
{
    if(draw_color_beam)
        return;
    if(draw_eraser == true)
    {
        eraser_color=Qt::green;
        ui->eraser_color_lbl->setStyleSheet("background-color:green");
    }
    else
    {
        pen_color=Qt::green;
        ui->pen_color_lbl->setStyleSheet("background-color:green");
    }
    pen.setColor(Qt::green);
}

void paint::slot_orange()
{
    if(draw_color_beam)
        return;
    if(draw_eraser == true)
    {
        eraser_color=QColor("orange");
        ui->eraser_color_lbl->setStyleSheet("background-color:orange");
    }
    else
    {
        pen_color=QColor("orange");
        ui->pen_color_lbl->setStyleSheet("background-color:orange");
    }
    pen.setColor(QColor("orange"));
}

void paint::slot_red()
{
    if(draw_color_beam)
        return;
    if(draw_eraser == true)
    {
           eraser_color=Qt::red;
           ui->eraser_color_lbl->setStyleSheet("background-color:red");
    }
    else
    {
           pen_color=Qt::red;
           ui->pen_color_lbl->setStyleSheet("background-color:red");
    }
       pen.setColor(Qt::red);
}

void paint::slot_white()
{
    if(draw_color_beam)
        return;
    if(draw_eraser == true)
    {
           eraser_color=Qt::white;
           ui->eraser_color_lbl->setStyleSheet("background-color:white");
    }
    else
    {
           pen_color=Qt::white;
           ui->pen_color_lbl->setStyleSheet("background-color:white");
    }
       pen.setColor(Qt::white);
}

void paint::set_color()
{
    if(draw_color_beam)
        return;

    QColor pallete_color=QColorDialog::getColor();
    pen.setColor(pallete_color);

    if(draw_eraser)
    {
       eraser_color=pallete_color;
       ui->eraser_color_lbl->setStyleSheet("background-color:"+eraser_color.name());
    }
    else
    {
        pen_color=pallete_color;
        ui->pen_color_lbl->setStyleSheet("background-color:"+pen_color.name());
    }
}

void paint::set_size(int w)
{
    pen.setWidth(w);
}


void paint::slot_pen_1()
{
    pen.setColor(QColor(pen_color));
    draw_tool(1,0,0,0,0,0);
    cursor(1);
}

void paint::slot_rubber_2()
{
    pen.setColor(eraser_color);
    draw_tool(0,1,0,0,0,0);
    cursor(2);
}

void paint::slot_line_3()
{
    pen.setColor(pen_color);
    draw_tool(0,0,1,0,0,0);
    cursor(3);
}

void paint::slot_rectangle_4()
{
    pen.setColor(pen_color);
    draw_tool(0,0,0,1,0,0);
    cursor(3);
}

void paint::slot_elipse_5()
{
    pen.setColor(pen_color);
    draw_tool(0,0,0,0,1,0);
    cursor(3);
}

void paint::slot_color_beam_6()
{
    draw_tool(0,0,0,0,0,1);
    cursor(3);
}


void paint::mousePressEvent(QMouseEvent *event)
{
 if (event->button() == Qt::LeftButton)
 {
     if(draw_pen || draw_eraser)
     {
     is_pressed = true;
     QPoint correct_pos;
     correct_pos.setX(event->pos().x());
     correct_pos.setY(event->pos().y()-90);
     list.push_back(correct_pos);
     return;
     }

     if(draw_line)
     {
         QToolTip::showText(event->pos(),
                            "Move and release the mouse to draw a LINE",
                            this);
         is_pressed = true;
         QPoint correct_pos;
         correct_pos.setX(event->pos().x());
         correct_pos.setY(event->pos().y()-90);
         one=correct_pos;
         two=one;
         return;
     }

     if(draw_rectangle)
     {
         QToolTip::showText(event->pos(),
                            "Move and release the mouse to draw a RECTANGLE",
                            this);
         is_pressed = true;
         QPoint correct_pos;
         correct_pos.setX(event->pos().x());
         correct_pos.setY(event->pos().y()-90);
         one=correct_pos;
         two=one;
         return;
     }

     if(draw_ellipse)
     {
         QToolTip::showText(event->pos(),
                            "Move and release the mouse to draw an ELLIPSE",
                            this);
         is_pressed = true;
         QPoint correct_pos;
         correct_pos.setX(event->pos().x());
         correct_pos.setY(event->pos().y()-90);
         one=correct_pos;
         two=one;
         return;
     }

     if(draw_color_beam)
     {
         is_pressed = true;
         QPoint correct_pos;
         correct_pos.setX(event->pos().x());
         correct_pos.setY(event->pos().y()-90);
         one=correct_pos;
         return;
     }
}}

void paint::mouseMoveEvent(QMouseEvent *event)
{
    if (!is_pressed || draw_line || draw_line || draw_ellipse)
        return;

    if(draw_pen || draw_eraser)
    {
      QPoint correct_pos;
      correct_pos.setX(event->pos().x());
      correct_pos.setY(event->pos().y()-90);
      list.push_back(correct_pos);
      this->update();
    }

    if(draw_color_beam){
        QPoint correct_pos;
        correct_pos.setX(event->pos().x());
        correct_pos.setY(event->pos().y()-90);
        two=correct_pos;
        this->update();
    }
}

void paint::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(draw_pen || draw_eraser)
        {
        is_pressed = false;
        QPoint correct_pos;
        correct_pos.setX(event->pos().x());
        correct_pos.setY(event->pos().y()-90);
        list.push_back(correct_pos);
        this->update();
        list.clear();
        }

        if(draw_line || draw_rectangle || draw_ellipse)
        {
            QPoint correct_pos;
            correct_pos.setX(event->pos().x());
            correct_pos.setY(event->pos().y()-90);
            two = correct_pos;
            this->update();
            return;
        }

        if(draw_color_beam)
        {
            is_pressed = false;
            one.setX(0);
            one.setY(0);
            two=one;
            ui->paper_label->setPixmap(QPixmap::fromImage(image));
            return;
        }
}}

void paint::paintEvent(QPaintEvent *)
{
    if(is_pressed == true)
    {
        if(draw_pen == true || draw_eraser)
        {
            QPainter painter;
            painter.begin(&image);
            if (list.size() < 2) return;
            painter.setPen(pen);
            for(int i=0;i<list.size()-1;i++)
                painter.drawLine(list[i],list[i+1]);
            painter.end();
            ui->paper_label->setPixmap(QPixmap::fromImage(image));
        }

        if( draw_line == true)
        {
            if( one != two )
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawLine(one,two);
                painter.end();
                is_pressed = false;
                one.setX(0);
                one.setY(0);
                two=one;
                ui->paper_label->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }

        if( draw_rectangle == true)
        {
            if( one != two )
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawRect(QRect(one,two));
                painter.end();
                is_pressed = false;
                one.setX(0);
                one.setY(0);
                two=one;
                ui->paper_label->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }

        if( draw_ellipse == true)
        {
            if( one != two )
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawEllipse(QRect(one,two));
                painter.end();
                is_pressed = false;
                one.setX(0);
                one.setY(0);
                two=one;
                ui->paper_label->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }

        if(draw_color_beam == true)
        {
            if( one != two )
            {
                pen.setColor(QColor(QRandomGenerator::global()->bounded(255),
                                QRandomGenerator::global()->bounded(255),
                                QRandomGenerator::global()->bounded(255)));
                brush.setColor(pen.color());
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawLine(QLineF(one,two));
                ui->paper_label->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }
}}
