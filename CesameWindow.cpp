#include "CesameWindow.h"

#include <iostream>

#include <qtimer.h>

#include <QIODevice>
#include <QMessageBox>
#include <QTcpSocket>

// Socket Test
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace Cesame;

CesameWindow::CesameWindow(QWidget *parent)
    : QWidget{parent}
{
    // Begin Socket Stuff
    std::cout << "Creating socket." << std::endl;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        std::cout << "Invalid address / Address not supported" << std::endl;
    }

    std::cout << "Connecting." << std::endl;
    int res = ::connect(sockfd, (struct sockaddr*) &address, sizeof(address));
    assert(res != -1);

    std::cout << "Reading." << std::endl;
    char buffer[1024];
    res = read(sockfd, &buffer, sizeof(buffer));
    assert(res > 0);

    std::cout << buffer << std::endl;

    ::close(sockfd);
    // End socket stuff

    timer = new QTimer(this);
    // What in the world even is this syntax? Anyway it makes sure the window updates every frameTime;
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CesameWindow::update));

    timer->start(frameTime);

    // Hacky workaround to get a translucent dark background, not just transparent
    background = new QWidget(this);
    background->lower();
    background->setFixedSize(this->size());

    setStyleSheet("background-color: rgba(14, 16, 24, 128);");
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TintedBackground, true); // TODO: Look into that, probably does nothing.
    setAttribute(Qt::WA_StyledBackground, true);

    update();
}

void CesameWindow::resizeEvent(QResizeEvent *event) {
    background->setFixedSize(this->size());
}

