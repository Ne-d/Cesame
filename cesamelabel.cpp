#include "cesamelabel.h"

CesameLabel::CesameLabel(CesameWindow *parent)
    : QWidget{parent}
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&CesameLabel::updateData));
}

void CesameLabel::updateData()
{

}
