#include "dockwidgetconfig.h"

DockWidgetConfig::DockWidgetConfig():
    QDockWidget()
{
    connect(this,SIGNAL(itemListChanged()),this,SLOT(handlerItemListChanged()));

    titulo.SeparadorFrame = new QFrame();
    titulo.SeparadorFrame->setFrameShape(QFrame::HLine);
    titulo.TituloLabel = new QLabel();
    titulo.isTit=false;
    titulo.isSeparador=false;
    mainVLayout = new QVBoxLayout();
    mainGroupBox = new QGroupBox();
    lastSpacer = new QSpacerItem(10,10,QSizePolicy::Maximum,QSizePolicy::Expanding);
    mainGroupBox->setLayout(mainVLayout);
    this->setWidget(mainGroupBox);
    mainVLayout->addSpacerItem(lastSpacer);

/*
    //DEBUG
    QLabel *aux = new QLabel("WOOYYYYYYYYYYYYY");
    QSpinBox *aux2 = new QSpinBox();
    QHBoxLayout *layaux = new QHBoxLayout();
    layaux->addWidget(aux2);
    layaux->addWidget(aux);
    mainVLayout->addLayout(layaux);
*/

    itemList.clear();
}

DockWidgetConfig::~DockWidgetConfig()
{

    for (int i=0;i< itemList.size() ; i++)
    {
        itemDockWidgetConfig_t *aux = itemList.at(i);
        delete aux->DoubleSpinBox;
        delete aux->localHLayout;
        delete aux->localVLayout;
        delete aux->Slider;
        delete aux->Spinbox;
        delete aux->Titulo;
        delete aux;
    }
    itemList.clear();
    //delete lastSpacer; //no se puede deletear lastSpacer. No se xq. Causa un CoC (crash on closing)
    delete titulo.SeparadorFrame;
    delete titulo.TituloLabel;
}


/*
QSize DockWidgetConfig::sizeHint () const
{
    return QSize(10,10);
}*/

void DockWidgetConfig::addItem(itemDockWidgetConfig_t *item)
{
    itemList.push_back(item);
    emit itemListChanged();
}

void DockWidgetConfig::addItem(QString nombre, int rangeMin, int rangeMax, int statingPoint)
{
    itemDockWidgetConfig_t *item = new itemDockWidgetConfig_t;
    item->Titulo = new QLabel(nombre);
    item->Slider = new QSlider( Qt::Horizontal);
    item->Slider->setRange(rangeMin,rangeMax);
    item->Slider->setSliderPosition(statingPoint);
    item->DoubleSpinBox=NULL;
    item->isDouble = false;
    item->Spinbox = new QSpinBox();
    item->Spinbox->setRange(rangeMin,rangeMax);
    item->Spinbox->setValue(statingPoint);

    item->localHLayout = new QHBoxLayout();
    item->localVLayout = new QVBoxLayout();

    itemList.push_back(item);
    emit itemListChanged();
}

void DockWidgetConfig::addItem(QString nombre, float rangeMin, float rangeMax, float statingPoint)
{
    itemDockWidgetConfig_t *item = new itemDockWidgetConfig_t;
    item->Titulo = new QLabel(nombre);
    item->Slider = new QSlider( Qt::Horizontal );
    item->Slider->setRange(rangeMin,rangeMax);
    item->Slider->setSliderPosition(statingPoint);
    item->Spinbox=NULL;
    item->isDouble = true;
    item->DoubleSpinBox = new QDoubleSpinBox();
    item->DoubleSpinBox->setRange(rangeMin,rangeMax);
    item->DoubleSpinBox->setValue(statingPoint);

    item->localHLayout = new QHBoxLayout();
    item->localVLayout = new QVBoxLayout();

    itemList.push_back(item);
    emit itemListChanged();
}


void DockWidgetConfig::setItems(QVector<itemDockWidgetConfig_t *> list)
{
    for (int i=0;i< itemList.size() ; i++)
    {
        itemDockWidgetConfig_t *aux = itemList.at(i);

        delete aux->DoubleSpinBox;
        delete aux->localHLayout;
        delete aux->localVLayout;
        delete aux->Slider;
        delete aux->Spinbox;
        delete aux->Titulo;
        delete aux;
    }
    itemList.clear();
    itemList = list;
    emit itemListChanged();
}

void DockWidgetConfig::removeItemAt(int index)
{
    itemDockWidgetConfig_t *auxItem = itemList.at(index);
    itemList.removeAt(index);

    delete auxItem->Slider;
    delete auxItem->Spinbox;
    delete auxItem->Titulo;
    delete auxItem->DoubleSpinBox;
    delete auxItem->localHLayout;
    delete auxItem->localVLayout;
    emit itemListChanged();
}

void DockWidgetConfig::removeItem(itemDockWidgetConfig_t *itemPtr)
{
    itemList.removeOne(itemPtr);
    itemDockWidgetConfig_t *auxItem = itemPtr;
    delete auxItem->Slider;
    delete auxItem->Spinbox;
    delete auxItem->Titulo;
    delete auxItem->DoubleSpinBox;
    delete auxItem->localHLayout;
    delete auxItem->localVLayout;
    emit itemListChanged();
}

void DockWidgetConfig::clearItems()
{
    for (int i=0;i< itemList.size() ; i++)
    {
        itemDockWidgetConfig_t *aux = itemList.at(i);

        delete aux->DoubleSpinBox;
        delete aux->localHLayout;
        delete aux->localVLayout;
        delete aux->Slider;
        delete aux->Spinbox;
        delete aux->Titulo;
        delete aux;
    }
    itemList.clear();
    emit itemListChanged();
}

int DockWidgetConfig::indexOf(itemDockWidgetConfig_t *itemPtr)
{
    return itemList.indexOf(itemPtr);
}

itemDockWidgetConfig_t* DockWidgetConfig::getItemAt(int index)
{
    return itemList.at(index);
}

QVector<itemDockWidgetConfig_t *> DockWidgetConfig::getItems()
{
    QVector<itemDockWidgetConfig_t *> aux = itemList;
    return aux;
}

int DockWidgetConfig::itemCount()
{
    return itemList.count();
}

void DockWidgetConfig::handlerItemListChanged()
{
    //remove current layouts & items
    for (int i=0;i< itemList.size() ; i++)
    {
        itemDockWidgetConfig_t *aux = itemList.at(i);
        //tema signals:desconecto todo, total desp se vuelven a conectar
        if (aux->isDouble)
            aux->DoubleSpinBox->disconnect();
        else
            aux->Spinbox->disconnect();
        aux->Slider->disconnect();

        aux->localHLayout->removeWidget(aux->Slider);
        if (aux->isDouble)
            aux->localHLayout->removeWidget(aux->DoubleSpinBox);
        else
            aux->localHLayout->removeWidget(aux->Spinbox);
        aux->localVLayout->removeWidget(aux->Titulo);
        aux->localVLayout->removeItem(aux->localHLayout);
        mainVLayout->removeItem(aux->localVLayout);
    }
    if (titulo.isTit)
        mainVLayout->removeWidget(titulo.TituloLabel);
    if (titulo.isSeparador)
        mainVLayout->removeWidget(titulo.SeparadorFrame);
    while (mainVLayout->takeAt(0));//este ultimo para borrar el spacer que no se como se hace xq no es qwidget



    //Set Titulo
    if (titulo.isTit)
    {
        mainVLayout->addWidget(titulo.TituloLabel);
    }
    if (titulo.isSeparador)
    {
        mainVLayout->addWidget(titulo.SeparadorFrame);
    }
    //Set Items & connections
    for (int i=0;i< itemList.size() ; i++)
    {
        itemList.at(i)->localVLayout->addWidget(itemList.at(i)->Titulo);
        itemList.at(i)->localHLayout->addWidget(itemList.at(i)->Slider);
        if (itemList.at(i)->isDouble)
            itemList.at(i)->localHLayout->addWidget(itemList.at(i)->DoubleSpinBox);
        else
            itemList.at(i)->localHLayout->addWidget(itemList.at(i)->Spinbox);
        itemList.at(i)->localVLayout->addLayout(itemList.at(i)->localHLayout);
        mainVLayout->addLayout(itemList.at(i)->localVLayout);

        void (QSlider:: *slideValueChanged) (int) = &QSlider::valueChanged;
        connect(itemList.at(i)->Slider,slideValueChanged,[this,i](int arg) {
            QString id = QString::number(i) + "," + QString::number(arg);
            emit itemParamChanged(id);
        } );

        if (itemList.at(i)->isDouble)
        {
            void (QDoubleSpinBox:: *dSpinValueChanged) (double) = &QDoubleSpinBox::valueChanged;
            connect(itemList.at(i)->DoubleSpinBox,dSpinValueChanged,[this,i](double arg) {
                QString id = QString::number(i) + "," + QString::number(arg);
                emit itemParamChanged(id);
            } );
            connect(itemList.at(i)->Slider,SIGNAL(valueChanged(int)),itemList.at(i)->DoubleSpinBox,SLOT(setValue(double)));
            connect(itemList.at(i)->DoubleSpinBox,SIGNAL(valueChanged(double)),itemList.at(i)->Slider,SLOT(setValue(int)));
        }
        else
        {
            void (QSpinBox:: *spinValueChanged) (int) = &QSpinBox::valueChanged;
            connect(itemList.at(i)->Spinbox,spinValueChanged,[this,i](int arg) {
                QString id = QString::number(i) + "," + QString::number(arg);
                emit itemParamChanged(id);
            } );
            connect(itemList.at(i)->Slider,SIGNAL(valueChanged(int)),itemList.at(i)->Spinbox,SLOT(setValue(int)));
            connect(itemList.at(i)->Spinbox,SIGNAL(valueChanged(int)),itemList.at(i)->Slider,SLOT(setValue(int)));
        }
    }
    //&& last spacer
    mainVLayout->addSpacerItem(lastSpacer);
}


void DockWidgetConfig::setTitulo(QString tit)
{
    titulo.TituloLabel->setText(tit);
    titulo.isTit = true;
    emit itemListChanged();
}

QString DockWidgetConfig::getTitulo()
{
    return titulo.TituloLabel->text();
}

void DockWidgetConfig::setSeparador(bool isSep)
{
    titulo.isSeparador=isSep;
    emit itemListChanged();
}


void DockWidgetConfig::toggleShowHide()
{
    if (this->isHidden())
        this->show();
    else
        this->hide();
}
