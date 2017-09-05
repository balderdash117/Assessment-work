using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Snakes_and_Ladders
{
    public partial class StartUpForm : Form
    {
        public string name1;
        public string name2;
        public string name3;
        public string name4;

        public StartUpForm()
        {
            InitializeComponent();
        }

        private void ButtonBegin_Click(object sender, EventArgs e)
        {
            int NumberOfPlayers;
            NumberOfPlayers = (int)numericOfPlayers.Value;

            name1 = player1name.Text;
            name2 = player2name.Text;
            name3 = player3name.Text;
            name4 = player4name.Text;

            Form1 FormMain = new Form1();
            FormMain.PlayersNumber = NumberOfPlayers;
            FormMain.Show();
            this.Hide();
            
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            switch (int.Parse(numericOfPlayers.Value.ToString()))
            {
                case 2:
                    player3GB.Enabled = false;
                    player4GB.Enabled = false;
                    break;
                case 3:
                    player3GB.Enabled = true;
                    player4GB.Enabled = false;
                    break;
                case 4:
                    player3GB.Enabled = true;
                    player4GB.Enabled = true;
                    break;
            }
        }

        private void player1imageButton_Click(object sender, EventArgs e)
        {
            images.Filter = "image files (*.jpg, *.png) | *.jpg; *.png";
            images.Title = "Please choose a new image for " + player1name.Text;

            if (images.ShowDialog() == DialogResult.OK)
            {
                PlayerPic1.Image = new Bitmap(images.FileName);
            }

            images.Dispose();
        }

        private void player2imageButton_Click(object sender, EventArgs e)
        {
            images.Filter = "image files (*.jpg, *.png) | *.jpg; *.png";
            images.Title = "Please choose a new image for " + player2name.Text;

            if (images.ShowDialog() == DialogResult.OK)
            {
                PlayerPic2.Image = new Bitmap(images.FileName);
            }

            images.Dispose();
        }

        private void player3imageButton_Click(object sender, EventArgs e)
        {
            images.Filter = "image files (*.jpg, *.png) | *.jpg; *.png";
            images.Title = "Please choose a new image for " + player3name.Text;

            if (images.ShowDialog() == DialogResult.OK)
            {
                PlayerPic3.Image = new Bitmap(images.FileName);
            }

            images.Dispose();
        }

        private void player4imageButton_Click(object sender, EventArgs e)
        {
            images.Filter = "image files (*.jpg, *.png) | *.jpg; *.png";
            images.Title = "Please choose a new image for " + player4name.Text;

            if (images.ShowDialog() == DialogResult.OK)
            {
                PlayerPic4.Image = new Bitmap(images.FileName);
            }

            images.Dispose();
        }
    }
}
