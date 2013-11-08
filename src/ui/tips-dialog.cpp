#include "tips-dialog.h"


TipsDialog::TipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TipsDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/seafile.png"));
    ui->mLogo->setPixmap(QPixmap(":/images/seafile-32.png"));

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
