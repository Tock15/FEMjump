#include "Player.h"
#include "platform.h"
#include "wall.h"
#include <QDebug>
#include <qevent.h>

Player::Player(): velocityY(0), isJumping(false), landed(false), facingDirection(1),velocityX(0), jumpPower(0), chargingJump(false)
{
    setPixmap(QPixmap(":/img/astolfoR.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::updatePosition);
    timer->start(16); // Runs every 16ms (~60 FPS)
    jumpChargeTimer = new QTimer(this);
    connect(jumpChargeTimer, &QTimer::timeout, this, &Player::increaseJumpPower);
}

void Player::goRight()
{
    if(facingDirection == 0){
        turn();
    }
    facingDirection = 1;
    setPos(x()+2,y());
}

void Player::goLeft()
{
    if(facingDirection == 1){
        turn();
    }
    facingDirection = 0;
    setPos(x()-2,y());
}

void Player::jump()
{
    if (!isJumping) {  // Prevent double jumps
        velocityY = -15;
        landed = false;
        isJumping = true;
    }
}
void Player::applyGravity(){
    const int maxFallSpeed = 20;
    velocityY += 1;  // Simulate gravity
    if (velocityY > maxFallSpeed) {
        velocityY = maxFallSpeed;
    }

    setPos(x(), y() + velocityY);
}
double lerp(double start, double end, double alpha) {
    return start + alpha * (end - start);
}
void Player::updatePosition() {
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    bool isOnPlatform = false;
    bool hitCeiling = false;

    // **1. Handle Vertical Movement (Ceiling & Floor Collisions)**
    for (QGraphicsItem *item : collidingItemsList) {
        Platform *platform = dynamic_cast<Platform *>(item);
        Wall *wall = dynamic_cast<Wall *>(item);
        Spike *spike  = dynamic_cast<Spike *>(item);
        if(spike){
            emit respawn();
        }

        QRectF playerRect = sceneBoundingRect();

        // **Ceiling Collision (Head Hits Wall)**
        if (wall && velocityY < 0) {
            QRectF wallRect = wall->sceneBoundingRect();
            bool horizontalOverlap = (playerRect.right() > wallRect.left()+10) &&
                                     (playerRect.left() < wallRect.right()-10);

            if (horizontalOverlap && playerRect.top() <= wallRect.bottom()) {
                velocityY = 0;  // Stop moving up
                setPos(x(), wallRect.bottom());  // Stay just below the ceiling
                hitCeiling = true;
                break;  // Stop checking further ceiling collisions
            }
        }

        // **Landing on Platform**
        if (platform) {
            QRectF platRect = platform->sceneBoundingRect();
            qreal playerBottom = playerRect.bottom();
            qreal platTop = platRect.top();
            bool horizontalOverlap = (playerRect.right() > platRect.left()) &&
                                     (playerRect.left() < platRect.right());

            if (velocityY > 0 && horizontalOverlap && playerBottom >= platTop) {
                setPos(x(), platTop - boundingRect().height());
                land();
                isOnPlatform = true;
                WinPlatform *winPlatform = dynamic_cast<WinPlatform *>(item);
                if(winPlatform){
                    qDebug() << "WIN!";
                }
                break;
            }
        }
    }

    // **Apply Gravity Only if Not on Platform or Ceiling**
    if (!isOnPlatform && !hitCeiling) {
        applyGravity();
    }

    // **2. Handle Horizontal Movement (Wall Bounces)**
    if (!hitCeiling) {  // Only apply side bounce if we're not hitting the ceiling
        for (QGraphicsItem *item : collidingItemsList) {
            Wall *wall = dynamic_cast<Wall *>(item);
            if (!wall) continue;

            QRectF playerRect = sceneBoundingRect();
            QRectF wallRect = wall->sceneBoundingRect();

            if(isJumping){
                if (velocityX > 0 && playerRect.right() >= wallRect.left() &&
                    playerRect.left() < wallRect.right()) {
                    velocityX = -(velocityX - 3);  // Reverse direction with energy loss
                    setPos(wallRect.left() - boundingRect().width(), y());
                }
                // **Left Wall Collision**
                else if (velocityX < 0 && playerRect.left() <= wallRect.right() &&
                         playerRect.right() > wallRect.left()) {
                    velocityX = -(velocityX + 3);  // Reverse direction with energy loss
                    setPos(wallRect.right(), y());
                }
            }
            if(!isJumping){
                if (x() + boundingRect().width() >= wall->getX()){
                    emit disableRight();
                }
                if(x() <= wall->getX() + wall->rect().width()){
                    emit disableLeft();
                }
            }
        }
    }

    // **Apply Horizontal Movement**
    if (isJumping) {
        setPos(x() + velocityX, y());
    }

    // **Boundary Bounces**
    if (x() <= -30 && velocityX < 0) {
        velocityX = -(velocityX + 3);
        setPos(-30, y());
    }
    if (x() + boundingRect().width() >= 620 && velocityX > 0) {
        velocityX = -(velocityX - 3);
        setPos(620 - boundingRect().width(), y());
    }

    // **Camera Follow Logic**
    QGraphicsScene *scene = this->scene();
    if (!scene || scene->views().isEmpty()) return;

    QGraphicsView *view = scene->views().first();
    QPointF targetCenter(x(), y() - 100);
    QPointF currentCenter = view->mapToScene(view->viewport()->rect().center());
    double smoothFactor = 0.1;
    QPointF newCenter(lerp(currentCenter.x(), targetCenter.x(), smoothFactor),
                      lerp(currentCenter.y(), targetCenter.y(), smoothFactor));

    view->centerOn(newCenter);

    //**Prevent Falling Too Far**
    if (y() > 1900) {
        setPos(x(), 1900);
        velocityY = 0;
        isJumping = false;
    }
}



void Player::land() {
    velocityY = 0;
    isJumping = false;
}
int Player::getVelocityY() const {
    return velocityY;
}
void Player::turn(){
    if(facingDirection == 1){ // turn left
        setPixmap(QPixmap(":/img/astolfo.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(facingDirection == 0){ // turn right
        setPixmap(QPixmap(":/img/astolfoR.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
void Player::startChargingJump() {
    if (!isJumping) {
        chargingJump = true;
        jumpPower = 5; // Start with a minimum jump power
        velocityX = 0;
        jumpChargeTimer->start(25);
        qDebug() << "Jump charging started!";
    }
}

void Player::increaseJumpPower() {
    if (chargingJump && jumpPower < 25 ) { // Cap max power
        jumpPower++;
        if(facingDirection == 0 && velocityX > -10){
            velocityX -=0.5;
        }
        else if(facingDirection == 1 && velocityX <10){
            velocityX +=0.5;
        }
        qDebug() << "Charging jump power: " << jumpPower;
        qDebug() << "Charging sideway power: " << velocityX;
    }
}
bool Player::isChargingJump()  {
    return chargingJump;
}
void Player::releaseJump() {
    if (chargingJump) {
        velocityY = -jumpPower; // Apply charged jump
        isJumping = true;
        chargingJump = false;
        jumpPower = 0;
        jumpChargeTimer->stop();
        qDebug() << "Jump released! Power: " << velocityY;
    }
}

double Player::getVelocityX(){
    return velocityX;
}
void Player::setVelocityX(double newV){
    velocityX = newV;
}
