#include "dockwidgetimages.h"


DockWidgetImages::DockWidgetImages():
    DockWidgetConfig()
{
    imageParameters.brilloValue=0;
    imageParameters.contrastValue=0;
    imageParameters.matizValue=0;
    imageParameters.saturaValue=0;
    this->addItem("Brillo",-100,100,imageParameters.brilloValue);
    this->addItem("Contraste",-100,100,imageParameters.contrastValue);
    this->addItem("Matiz",-100,100,imageParameters.matizValue);
    this->addItem("Saturacion",-100,100,imageParameters.contrastValue);
    this->setWindowTitle("Editar imagen");

    this->setTitulo("Modifique los valores de los siguientes \nparametros para modificar la imagen.");
    this->setSeparador(true);

    connect(this,SIGNAL(itemParamChanged(QString)),this,SLOT(handlerParametroChanged(QString)));
}

DockWidgetImages::~DockWidgetImages()
{

}


void DockWidgetImages::handlerParametroChanged(QString id)
{
    if (id.split(",").size() != 2)
    {
        qDebug() << "Error de id: Cant de campos != 2";
        return;
    }
    int value = id.split(",").at(1).toInt();
    switch (id.split(",").at(0).toInt())
    {
    case BRILLO:
        imageParameters.brilloValue=value;
        emit sBrilloChanged(value);
        break;
    case CONTRASTE:
        imageParameters.contrastValue=value;
        emit sContrastChanged(value);
        break;
    case MATIZ:
        imageParameters.matizValue=value;
        emit sMatizChanged(value);
        break;
    case SATURACION:
        imageParameters.saturaValue=value;
        emit sSaturaChanged(value);
        break;
    default:
        qDebug() << "Error de id: ID out of range";
        break;
    }
}

paramImagen_t DockWidgetImages::getCurrentParameters()
{
    return imageParameters;
}
