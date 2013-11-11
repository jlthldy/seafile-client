#include "tips-dialog.h"


TipsDialog::TipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TipsDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/seafile.png"));
    ui->mLogo->setPixmap(QPixmap(":/images/seafile-32.png"));
    ui->label_4->setStyleSheet("color:grey");
    ui->label_4->setAlignment(Qt::AlignHCenter);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

TipsDialog::~TipsDialog()
{
    delete ui;
}

void TipsDialog::okButtonClicked()
{
    close();
}
