#include <iostream>
#include <experimental/random>
#include "MyScene.h"
#include <QTimer>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPainter>

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent)
{
	setSceneRect(0, 0, 1200, 700);
	background = new QPixmap("assets/background.jpg");
	this->game = true;

	rect = new QGraphicsRectItem(0, 1, 1200, 20);
	rect->setBrush(QBrush(Qt::white));
	this->addItem(rect);

	vie = 3;
	vie_text = new QGraphicsTextItem(QStringLiteral("Vie : %1").arg(vie));
	vie_text->setPos(1150, 0);
	this->addItem(vie_text);

	best_score = 0;
	score = 0;
	score_text = new QGraphicsTextItem(QStringLiteral("Score : %1").arg(score));
	score_text->setPos(550, 0);
	this->addItem(score_text);

	best_score_text = new QGraphicsTextItem(QStringLiteral("Meilleur score : %1").arg(best_score));
	best_score_text->setPos(0, 0);
	this->addItem(best_score_text);

	adversary = new QGraphicsPixmapItem(QPixmap("assets/adversary.png").scaled(100, 100));
	adversary->setPos(550, 20);
	this->addItem(adversary);

	bonus = new QGraphicsPixmapItem(QPixmap("assets/bonus.png").scaled(50, 50));
	bonus->setPos(std::experimental::randint(0, 1100), 20);
	bonus_speed = 5;
	this->addItem(bonus);

	adversary_speed = 7;
	progress_speed = 0;
	player = new QGraphicsPixmapItem(QPixmap("assets/character.png").scaled(100, 100));
	player->setPos(550, 599);
	this->addItem(player);

	player_speed = 10;
	move_up = false;
	move_down = false;
	move_right = false;
	move_left = false;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16);
}

void MyScene::update()
{
	if (game) {
		if (this->move_up) {
			this->player->setPos(this->player->pos().rx(), this->player->pos().ry() - this->player_speed);
		}
		if (this->player->pos().ry() <= 20) { this->player->setPos(this->player->pos().rx(), 21); }

		if (this->move_down) {
			this->player->setPos(this->player->pos().rx(), this->player->pos().ry() + this->player_speed);
		}
		if (this->player->pos().ry() >= 600) { this->player->setPos(this->player->pos().rx(), 599); }

		if (this->move_right) {
			this->player->setPos(this->player->pos().rx() + this->player_speed, this->player->pos().ry());
		}
		if (this->player->pos().rx() >= 1100) { this->player->setPos(1099, this->player->pos().ry()); }

		if (this->move_left && this->player->pos().rx() > 0) {
			this->player->setPos(this->player->pos().rx() - this->player_speed, this->player->pos().ry());
		}
		if (this->player->pos().rx() <= 0) { this->player->setPos(1, this->player->pos().ry()); }

		if (this->adversary->pos().ry() + 1 < 600) {
			this->adversary->setPos(this->adversary->pos().rx(), this->adversary->pos().ry() + this->adversary_speed);
			if (this->adversary->pos().ry() > 600) {
				this->adversary->setPos(this->adversary->pos().rx(), 600);
			}
		} else {
			if (this->adversary_speed < 17) {
				this->progress_speed++;
				if (this->progress_speed == this->adversary_speed) {
					this->progress_speed = 0;
					this->adversary_speed++;
				}
			}
			this->adversary->setPos(std::experimental::randint(0, 1100), 20);
		}

		if (this->bonus->pos().ry() + 1 < 650) {
			this->bonus->setPos(this->bonus->pos().rx(), this->bonus->pos().ry() + this->bonus_speed);
			if (this->bonus->pos().ry() > 650) {
				this->bonus->setPos(this->bonus->pos().rx(), 650);
			}
		} else {
			this->bonus->setPos(std::experimental::randint(0, 1100), 20);
		}

		if (this->player->collidesWithItem(this->adversary)) {
			this->vie--;
			this->vie_text->setPlainText(QStringLiteral("Vie : %1").arg(this->vie));
			if (this->vie == 0) {
				this->game = false;
			}
			reset_adversary();
		} else {
			add_score(1);
		}

		if (this->player->collidesWithItem(this->bonus)) {
			add_score(100);
			reset_bonus();
		}
	}
}

void MyScene::reset_adversary()
{
	this->adversary->setPos(std::experimental::randint(0, 1100), 20);
}

void MyScene::reset_player()
{
	this->player->setPos(550, 599);
}

void MyScene::reset_bonus()
{
	this->bonus->setPos(std::experimental::randint(0, 1100), 20);
}

void MyScene::reset_game()
{
	this->game = true;
	this->vie = 3;
	this->vie_text->setPlainText(QStringLiteral("Vie : %1").arg(this->vie));
	this->score = 0;
	this->score_text->setPlainText(QStringLiteral("Score : %1").arg(this->score));
	this->adversary->setPos(550, 20);
	this->adversary_speed = 7;
	this->progress_speed = 0;
	reset_bonus();
	reset_player();
}

void MyScene::add_score(int number)
{
	this->score += number;
	this->score_text->setPlainText(QStringLiteral("Score : %1").arg(this->score));
	if (this->score > this->best_score) {
		this->best_score = this->score;
		this->best_score_text->setPlainText(QStringLiteral("Meilleur score : %1").arg(this->best_score));
	}
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Z) {
		this->move_up = true;
	} else if (event->key() == Qt::Key_S) {
		this->move_down = true;
	} else if (event->key() == Qt::Key_D) {
		this->move_right = true;
	} else if (event->key() == Qt::Key_Q) {
		this->move_left = true;
	} else if (event->key() == Qt::Key_R && this->game == false) {
		reset_game();
	}
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Z) {
		this->move_up = false;
	} else if (event->key() == Qt::Key_S) {
		this->move_down = false;
	} else if (event->key() == Qt::Key_D) {
		this->move_right = false;
	} else if (event->key() == Qt::Key_Q) {
		this->move_left = false;
	}
}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);
	painter->drawPixmap(QPointF(0, 0), *background, sceneRect());
}