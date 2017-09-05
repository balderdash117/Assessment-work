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

    public partial class Form1 : Form
    {
        Random r = new Random();
        PictureBox[] MyBoard = new PictureBox[64];
        PlayerClass[] TurnPlayer = new PlayerClass[5];
        System.Windows.Forms.Form startUp = System.Windows.Forms.Application.OpenForms["StartUpForm"];
        private int _NoOfPlayers;
        int rollnumber;
        int dicenumber;
        int pturn;

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonRoll_Click(object sender, EventArgs e)
        {
            RollDice();
            pturn = int.Parse(WhoseTurn.Text);
            moveplayer(pturn, rollnumber);

            if (pturn == _NoOfPlayers)
            {
                WhoseTurn.Text = "1";
                turnplayerimage.Image = PlayerPic1.Image;
                        label1.Enabled = true;
                        PlayerPic1.Enabled = true;
                        label2.Enabled = false;
                        PlayerPic2.Enabled = false;
                        label3.Enabled = false;
                        PlayerPic3.Enabled = false;
                        label4.Enabled = false;
                        PlayerPic4.Enabled = false;
                switch (_NoOfPlayers)
                {
                    case 1:
                              
                        break;
                    case 2:
                        MessageBox.Show("It is now player 1's turn, please take your roll.");
                        break;
                    case 3:
                        MessageBox.Show("It is now player 1's turn, please take your roll.");
                        break;
                    case 4:
                        MessageBox.Show("It is now player 1's turn, please take your roll.");
                        break;

                }
            }
            else
            {
                pturn = pturn + 1;
                WhoseTurn.Text = pturn.ToString();
                switch (pturn)
                {
                    case 2:
                        turnplayerimage.Image = PlayerPic2.Image;
                        label1.Enabled = false;
                        PlayerPic1.Enabled = false;
                        label2.Enabled = true;
                        PlayerPic2.Enabled = true;
                        MessageBox.Show("It is now player 2's turn, please take your roll.");
                        break;
                    case 3:
                        turnplayerimage.Image = PlayerPic3.Image;
                        label1.Enabled = false;
                        PlayerPic1.Enabled = false;
                        label2.Enabled = false;
                        PlayerPic2.Enabled = false;
                        label3.Enabled = true;
                        PlayerPic3.Enabled = true;
                        MessageBox.Show("It is now player 3's turn, please take your roll.");
                        break;
                    case 4:
                        turnplayerimage.Image = PlayerPic4.Image;
                        label1.Enabled = false;
                        PlayerPic1.Enabled = false;
                        label2.Enabled = false;
                        PlayerPic2.Enabled = false;
                        label3.Enabled = false;
                        PlayerPic3.Enabled = false;
                        label4.Enabled = true;
                        PlayerPic4.Enabled = true;
                        MessageBox.Show("It is now player 4's turn, please take your roll.");
                        break;
                }
            }
        }

        private void RollDice()
        {                        
            dicenumber = r.Next(1, 7);
            rollnumber = dicenumber;

            switch (dicenumber)
            {
                case 1:
                    PictureDice.Image = dice1.Image;
                    break;
                case 2:
                    PictureDice.Image = dice2.Image;
                    break;
                case 3:
                    PictureDice.Image = dice3.Image;
                    break;
                case 4:
                    PictureDice.Image = dice4.Image;
                    break;
                case 5:
                    PictureDice.Image = dice5.Image;
                    break;
                case 6:
                    PictureDice.Image = dice6.Image;
                    break;
                default:
                    break;

            }

        }
        #region this is un-needed code
        private void pictureBox6_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox7_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {

        }

        private void space50_Click(object sender, EventArgs e)
        {

        }

        private void space64_Click(object sender, EventArgs e)
        {

        }
        #endregion

        private void Form1_Load(object sender, EventArgs e)
        {
            createboardarray();
            createplayerarray();
            buttonRoll.Enabled = false;

            switch (_NoOfPlayers)
            {
                case 1:
                    label1.Visible = true;
                    PlayerPic1.Visible = true;
                    break;
                case 2:
                    label1.Visible = true;
                    PlayerPic1.Visible = true;
                    label2.Visible = true;
                    PlayerPic2.Visible = true;
                    break;
                case 3:
                    label1.Visible = true;
                    PlayerPic1.Visible = true;
                    label2.Visible = true;
                    PlayerPic2.Visible = true;
                    label3.Visible = true;
                    PlayerPic3.Visible = true;
                    break;
                case 4:
                    label1.Visible = true;
                    PlayerPic1.Visible = true;
                    label2.Visible = true;
                    PlayerPic2.Visible = true;
                    label3.Visible = true;
                    PlayerPic3.Visible = true;
                    label4.Visible = true;
                    PlayerPic4.Visible = true;
                    break;

            }
                
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }

        public int PlayersNumber
        {
            set { _NoOfPlayers = value; }
        }
        #region This is my array code
        private void createboardarray()
        {
            MyBoard[0] = space1;
            MyBoard[1] = space2;
            MyBoard[2] = space3;
            MyBoard[3] = space4;
            MyBoard[4] = space5;
            MyBoard[5] = space6;
            MyBoard[6] = space7;
            MyBoard[7] = space8;
            MyBoard[8] = space9;
            MyBoard[9] = space10;
            MyBoard[10] = space11;
            MyBoard[11] = space12;
            MyBoard[12] = space13;
            MyBoard[13] = space14;
            MyBoard[14] = space15;
            MyBoard[15] = space16;
            MyBoard[16] = space17;
            MyBoard[17] = space18;
            MyBoard[18] = space19;
            MyBoard[19] = space20;
            MyBoard[20] = space21;
            MyBoard[21] = space22;
            MyBoard[22] = space23;
            MyBoard[23] = space24;
            MyBoard[24] = space25;
            MyBoard[25] = space26;
            MyBoard[26] = space27;
            MyBoard[27] = space28;
            MyBoard[28] = space29;
            MyBoard[29] = space30;
            MyBoard[30] = space31;
            MyBoard[31] = space32;
            MyBoard[32] = space33;
            MyBoard[33] = space34;
            MyBoard[34] = space35;
            MyBoard[35] = space36;
            MyBoard[36] = space37;
            MyBoard[37] = space38;
            MyBoard[38] = space39;
            MyBoard[39] = space40;
            MyBoard[40] = space41;
            MyBoard[41] = space42;
            MyBoard[42] = space43;
            MyBoard[43] = space44;
            MyBoard[44] = space45;
            MyBoard[45] = space46;
            MyBoard[46] = space47;
            MyBoard[47] = space48;
            MyBoard[48] = space49;
            MyBoard[49] = space50;
            MyBoard[50] = space51;
            MyBoard[51] = space52;
            MyBoard[52] = space53;
            MyBoard[53] = space54;
            MyBoard[54] = space55;
            MyBoard[55] = space56;
            MyBoard[56] = space57;
            MyBoard[57] = space58;
            MyBoard[58] = space59;
            MyBoard[59] = space60;
            MyBoard[60] = space61;
            MyBoard[61] = space62;
            MyBoard[62] = space63;
            MyBoard[63] = space64;
        }
        #endregion

        private void moveplayer(int whoturn, int rollingdie)
        {
            if (!TurnPlayer[whoturn].skipTurn)
            { 
                int newposition;
                int oldposition;
                int currentplayer;
                oldposition = TurnPlayer[whoturn].Position;
                newposition = TurnPlayer[whoturn].Position + rollingdie;
                TurnPlayer[whoturn].Position = newposition;
                switch (newposition)
                {
                    case 2:
                        MessageBox.Show("Congratulations, you landed on a ladder.");
                        newposition = 17;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 15:
                        pturn = pturn - 1;
                        MessageBox.Show("Congrats, you got an extra turn");
                        break;
                    case 18:
                        MessageBox.Show("Unlucky, you landed on a snake.");
                        newposition = 4;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 23:
                        MessageBox.Show("Congratulations, you landed on a ladder.");
                        newposition = 38;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 28:
                        MessageBox.Show("Congratulations, you landed on a ladder.");
                        newposition = 52;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 47:
                        MessageBox.Show("Congratulations, you landed on a ladder.");
                        newposition = 62;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 26:
                        MessageBox.Show("Unlucky, you landed on a snake.");
                        newposition = 7;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 57:
                        MessageBox.Show("Unlucky, you landed on a snake.");
                        newposition = 40;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 58:
                        pturn = pturn - 1;
                        MessageBox.Show("Congrats, you got an extra turn");
                        break;
                    case 61:
                        MessageBox.Show("Unlucky, you landed on a snake.");
                        newposition = 31;
                        TurnPlayer[whoturn].Position = newposition;
                        break;
                    case 42:
                        MessageBox.Show("Unlucky, you landed on a snake totem, you miss your next turn.");
                        TurnPlayer[whoturn].skipTurn = true;
                        break;
                    case 51:
                        MessageBox.Show("Unlucky, you landed on a snake totem, you miss your next turn.");
                        TurnPlayer[whoturn].skipTurn = true;
                        break;
                }

                currentplayer = whoturn;

                if (newposition >= 63)
                {
                    TurnPlayer[currentplayer].Position = 64;

                    MessageBox.Show(TurnPlayer[currentplayer].Name + " " + "is the winner");
                    MessageBox.Show("Thankyou for playing my game.");
                    MessageBox.Show("The application will now close automatically");

                    DialogResult result = MessageBox.Show("Would you like to save the results of this game?", "", MessageBoxButtons.YesNo);

                    if (result == DialogResult.Yes)
                    {
                        //Save logic
                        if (PlacingsFromGame.ShowDialog() == DialogResult.OK)
                        {
                            StreamWriter stream = new StreamWriter(PlacingsFromGame.FileName);
                            stream.WriteLine("Snakes and ladders Game Results");
                            ///Who won
                            ///

                            stream.WriteLine("Winner: " + TurnPlayer[currentplayer].Name);

                            ///Save positions of each other player
                            ///Correct the positions

                            int player1Pos = TurnPlayer[1].Position + 1;
                            int player2Pos = TurnPlayer[2].Position + 1;
                            int player3Pos = TurnPlayer[3].Position + 1;
                            int player4Pos = TurnPlayer[4].Position + 1;

                            ///Write them into the file
                            stream.WriteLine("Final Positions:");

                            switch (_NoOfPlayers)
                            {
                                case 1:
                                    stream.WriteLine(TurnPlayer[1].Name + "'s end position was " + player1Pos);
                                    break;
                                case 2:
                                    stream.WriteLine(TurnPlayer[1].Name + "'s end position was " + player1Pos);
                                    stream.WriteLine(TurnPlayer[2].Name + "'s end position was " + player2Pos);
                                    break;
                                case 3:
                                    stream.WriteLine(TurnPlayer[1].Name + "'s end position was " + player1Pos);
                                    stream.WriteLine(TurnPlayer[2].Name + "'s end position was " + player2Pos);
                                    stream.WriteLine(TurnPlayer[3].Name + "'s end position was " + player3Pos);
                                    break;
                                case 4:
                                    stream.WriteLine(TurnPlayer[1].Name + "'s end position was " + player1Pos);
                                    stream.WriteLine(TurnPlayer[2].Name + "'s end position was " + player2Pos);
                                    stream.WriteLine(TurnPlayer[3].Name + "'s end position was " + player3Pos);
                                    stream.WriteLine(TurnPlayer[4].Name + "'s end position was " + player4Pos);
                                    break;
                            }
                           
                            stream.WriteLine("");

                            stream.Close();
                        }
                    }

                    Application.Exit();
                }
                else
                {
                    if (oldposition < 0)
                    {
                        MyBoard[newposition].Image = turnplayerimage.Image;
                    }
                    else
                    {
                        MyBoard[newposition].Image = turnplayerimage.Image;
                        MyBoard[oldposition].Image = clearbox.Image;
                    }
                }
            }

            else
            {
                
                MessageBox.Show("Your turn is skipped this turn");
                TurnPlayer[whoturn].skipTurn = false;
                
            }
        }

        private void createplayerarray()
        {          
            PlayerClass Player1 = new PlayerClass();
            Player1.Name = ((StartUpForm)startUp).name1;
            Player1.Position = -1;
            Player1.Number = 1;
            Player1.skipTurn = false;
            PlayerClass Player2 = new PlayerClass();
            Player2.Name = ((StartUpForm)startUp).name2;
            Player2.Position = -1;
            Player2.Number = 2;
            Player2.skipTurn = false;
            PlayerClass Player3 = new PlayerClass();
            Player3.Name = ((StartUpForm)startUp).name3;
            Player3.Position = -1;
            Player3.Number = 3;
            Player3.skipTurn = false;
            PlayerClass Player4 = new PlayerClass();
            Player4.Name = ((StartUpForm)startUp).name4;
            Player4.Position = -1;
            Player4.Number = 4;
            Player4.skipTurn = false;

            TurnPlayer[1] = Player1;
            TurnPlayer[2] = Player2;
            TurnPlayer[3] = Player3;
            TurnPlayer[4] = Player4;

            label1.Text = Player1.Name;
            label2.Text = Player2.Name;
            label3.Text = Player3.Name;
            label4.Text = Player4.Name;
        }

        private void buttonstart_Click(object sender, EventArgs e)
        {
            label5.Visible = true;
            WhoseTurn.Visible = true;
            turnplayerimage.Visible = true;
            turnplayerimage.Image = PlayerPic1.Image;
            WhoseTurn.Text = "1";
            buttonRoll.Enabled = true;
            switch (_NoOfPlayers)
            {
                case 1:
                    label1.Enabled = true;
                    PlayerPic1.Enabled = true;
                    break;
                case 2:
                    label1.Enabled = true;
                    PlayerPic1.Enabled = true;
                    label2.Enabled = false;
                    PlayerPic2.Enabled = false;
                    break;
                case 3:
                    label1.Enabled = true;
                    PlayerPic1.Enabled = true;
                    label2.Enabled = false;
                    PlayerPic2.Enabled = false;
                    label3.Enabled = false;
                    PlayerPic3.Enabled = false;
                    break;
                case 4:
                    label1.Enabled = true;
                    PlayerPic1.Enabled = true;
                    label2.Enabled = false;
                    PlayerPic2.Enabled = false;
                    label3.Enabled = false;
                    PlayerPic3.Enabled = false;
                    label4.Enabled = false;
                    PlayerPic4.Enabled = false;
                    break;
                    
            }
            buttonstart.Visible = false;
        }
    }
}
