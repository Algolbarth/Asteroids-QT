#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>

class MyScene : public QGraphicsScene
{
Q_OBJECT
	bool game;
	int best_score;
	int score;
	int vie;
	int player_speed;
	int adversary_speed;
	int progress_speed;
	int bonus_speed;
	bool move_up;
	bool move_down;
	bool move_right;
	bool move_left;
	QTimer *timer;
	QGraphicsRectItem *rect;
	QGraphicsTextItem *vie_text;
	QGraphicsTextItem *score_text;
	QGraphicsTextItem *best_score_text;
	QGraphicsPixmapItem *adversary;
	QGraphicsPixmapItem *bonus;
	QGraphicsPixmapItem *player;
	QPixmap *background;
public:
	explicit MyScene(QObject *parent = nullptr);

	~MyScene() override = default;

	void keyPressEvent(QKeyEvent *event) override;

	void keyReleaseEvent(QKeyEvent *event) override;

	void drawBackground(QPainter *painter, const QRectF &rect) override;

	void reset_player();

	void reset_adversary();

	void reset_bonus();

	void reset_game();

	void add_score(int number);

public slots:

	void update();
};

#endif
