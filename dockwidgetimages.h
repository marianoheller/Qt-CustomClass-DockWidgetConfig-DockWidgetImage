#ifndef DOCKWIDGETIMAGES_H
#define DOCKWIDGETIMAGES_H

#include "dockwidgetconfig.h"

#define BRILLO      0
#define CONTRASTE   1
#define MATIZ       2
#define SATURACION  3

typedef struct{
    int brilloValue;
    int contrastValue;
    int matizValue;
    int saturaValue;
} paramImagen_t;

class DockWidgetImages: public DockWidgetConfig
{
    Q_OBJECT
public:
    DockWidgetImages();
    ~DockWidgetImages();
    paramImagen_t getCurrentParameters();
private slots:
    void handlerParametroChanged(QString id);
signals:
    sBrilloChanged(int value);
    sContrastChanged(int value);
    sMatizChanged(int value);
    sSaturaChanged(int value);
private:
    paramImagen_t imageParameters;
};

#endif // DOCKWIDGETIMAGES_H
