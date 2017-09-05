namespace Snakes_and_Ladders
{
    partial class StartUpForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StartUpForm));
            this.ButtonBegin = new System.Windows.Forms.Button();
            this.numericOfPlayers = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.options = new System.Windows.Forms.Label();
            this.player1BG = new System.Windows.Forms.GroupBox();
            this.player1imageButton = new System.Windows.Forms.Button();
            this.player1name = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.player2BG = new System.Windows.Forms.GroupBox();
            this.player2imageButton = new System.Windows.Forms.Button();
            this.player2name = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.player3GB = new System.Windows.Forms.GroupBox();
            this.player3imageButton = new System.Windows.Forms.Button();
            this.player3name = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.player4GB = new System.Windows.Forms.GroupBox();
            this.player4imageButton = new System.Windows.Forms.Button();
            this.player4name = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.PlayerPic1 = new System.Windows.Forms.PictureBox();
            this.PlayerPic4 = new System.Windows.Forms.PictureBox();
            this.PlayerPic3 = new System.Windows.Forms.PictureBox();
            this.PlayerPic2 = new System.Windows.Forms.PictureBox();
            this.images = new System.Windows.Forms.SaveFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.numericOfPlayers)).BeginInit();
            this.player1BG.SuspendLayout();
            this.player2BG.SuspendLayout();
            this.player3GB.SuspendLayout();
            this.player4GB.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic2)).BeginInit();
            this.SuspendLayout();
            // 
            // ButtonBegin
            // 
            this.ButtonBegin.Location = new System.Drawing.Point(469, 269);
            this.ButtonBegin.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.ButtonBegin.Name = "ButtonBegin";
            this.ButtonBegin.Size = new System.Drawing.Size(99, 34);
            this.ButtonBegin.TabIndex = 0;
            this.ButtonBegin.Text = "Begin";
            this.ButtonBegin.UseVisualStyleBackColor = true;
            this.ButtonBegin.Click += new System.EventHandler(this.ButtonBegin_Click);
            // 
            // numericOfPlayers
            // 
            this.numericOfPlayers.Location = new System.Drawing.Point(214, 116);
            this.numericOfPlayers.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.numericOfPlayers.Maximum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numericOfPlayers.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericOfPlayers.Name = "numericOfPlayers";
            this.numericOfPlayers.Size = new System.Drawing.Size(56, 20);
            this.numericOfPlayers.TabIndex = 1;
            this.numericOfPlayers.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericOfPlayers.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(30, 116);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(147, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Select the numbner of players";
            // 
            // options
            // 
            this.options.AutoSize = true;
            this.options.Location = new System.Drawing.Point(6, 98);
            this.options.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.options.Name = "options";
            this.options.Size = new System.Drawing.Size(43, 13);
            this.options.TabIndex = 3;
            this.options.Text = "Options";
            // 
            // player1BG
            // 
            this.player1BG.Controls.Add(this.player1imageButton);
            this.player1BG.Controls.Add(this.player1name);
            this.player1BG.Controls.Add(this.label5);
            this.player1BG.Location = new System.Drawing.Point(38, 148);
            this.player1BG.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player1BG.Name = "player1BG";
            this.player1BG.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player1BG.Size = new System.Drawing.Size(109, 106);
            this.player1BG.TabIndex = 8;
            this.player1BG.TabStop = false;
            this.player1BG.Text = "Player 1";
            // 
            // player1imageButton
            // 
            this.player1imageButton.Location = new System.Drawing.Point(14, 61);
            this.player1imageButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player1imageButton.Name = "player1imageButton";
            this.player1imageButton.Size = new System.Drawing.Size(89, 27);
            this.player1imageButton.TabIndex = 8;
            this.player1imageButton.Text = "Change Image";
            this.player1imageButton.UseVisualStyleBackColor = true;
            this.player1imageButton.Click += new System.EventHandler(this.player1imageButton_Click);
            // 
            // player1name
            // 
            this.player1name.Location = new System.Drawing.Point(14, 34);
            this.player1name.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player1name.Name = "player1name";
            this.player1name.Size = new System.Drawing.Size(78, 20);
            this.player1name.TabIndex = 2;
            this.player1name.Text = "Player 1";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 19);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Name";
            // 
            // player2BG
            // 
            this.player2BG.Controls.Add(this.player2imageButton);
            this.player2BG.Controls.Add(this.player2name);
            this.player2BG.Controls.Add(this.label4);
            this.player2BG.Location = new System.Drawing.Point(166, 148);
            this.player2BG.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player2BG.Name = "player2BG";
            this.player2BG.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player2BG.Size = new System.Drawing.Size(109, 106);
            this.player2BG.TabIndex = 9;
            this.player2BG.TabStop = false;
            this.player2BG.Text = "Player 2";
            // 
            // player2imageButton
            // 
            this.player2imageButton.Location = new System.Drawing.Point(12, 61);
            this.player2imageButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player2imageButton.Name = "player2imageButton";
            this.player2imageButton.Size = new System.Drawing.Size(89, 27);
            this.player2imageButton.TabIndex = 8;
            this.player2imageButton.Text = "Change Image";
            this.player2imageButton.UseVisualStyleBackColor = true;
            this.player2imageButton.Click += new System.EventHandler(this.player2imageButton_Click);
            // 
            // player2name
            // 
            this.player2name.Location = new System.Drawing.Point(12, 34);
            this.player2name.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player2name.Name = "player2name";
            this.player2name.Size = new System.Drawing.Size(78, 20);
            this.player2name.TabIndex = 3;
            this.player2name.Text = "Player 2";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 19);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Name";
            // 
            // player3GB
            // 
            this.player3GB.Controls.Add(this.player3imageButton);
            this.player3GB.Controls.Add(this.player3name);
            this.player3GB.Controls.Add(this.label3);
            this.player3GB.Enabled = false;
            this.player3GB.Location = new System.Drawing.Point(292, 148);
            this.player3GB.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player3GB.Name = "player3GB";
            this.player3GB.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player3GB.Size = new System.Drawing.Size(109, 106);
            this.player3GB.TabIndex = 9;
            this.player3GB.TabStop = false;
            this.player3GB.Text = "Player 3";
            // 
            // player3imageButton
            // 
            this.player3imageButton.Location = new System.Drawing.Point(13, 61);
            this.player3imageButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player3imageButton.Name = "player3imageButton";
            this.player3imageButton.Size = new System.Drawing.Size(89, 27);
            this.player3imageButton.TabIndex = 8;
            this.player3imageButton.Text = "Change Image";
            this.player3imageButton.UseVisualStyleBackColor = true;
            this.player3imageButton.Click += new System.EventHandler(this.player3imageButton_Click);
            // 
            // player3name
            // 
            this.player3name.Location = new System.Drawing.Point(13, 34);
            this.player3name.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player3name.Name = "player3name";
            this.player3name.Size = new System.Drawing.Size(78, 20);
            this.player3name.TabIndex = 3;
            this.player3name.Text = "Player 3";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 19);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Name";
            // 
            // player4GB
            // 
            this.player4GB.Controls.Add(this.player4imageButton);
            this.player4GB.Controls.Add(this.player4name);
            this.player4GB.Controls.Add(this.label2);
            this.player4GB.Enabled = false;
            this.player4GB.Location = new System.Drawing.Point(418, 148);
            this.player4GB.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player4GB.Name = "player4GB";
            this.player4GB.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player4GB.Size = new System.Drawing.Size(109, 106);
            this.player4GB.TabIndex = 9;
            this.player4GB.TabStop = false;
            this.player4GB.Text = "Player 4";
            // 
            // player4imageButton
            // 
            this.player4imageButton.Location = new System.Drawing.Point(13, 61);
            this.player4imageButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player4imageButton.Name = "player4imageButton";
            this.player4imageButton.Size = new System.Drawing.Size(89, 27);
            this.player4imageButton.TabIndex = 7;
            this.player4imageButton.Text = "Change Image";
            this.player4imageButton.UseVisualStyleBackColor = true;
            this.player4imageButton.Click += new System.EventHandler(this.player4imageButton_Click);
            // 
            // player4name
            // 
            this.player4name.Location = new System.Drawing.Point(13, 34);
            this.player4name.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.player4name.Name = "player4name";
            this.player4name.Size = new System.Drawing.Size(78, 20);
            this.player4name.TabIndex = 4;
            this.player4name.Text = "Player 4";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 19);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Name";
            // 
            // PlayerPic1
            // 
            this.PlayerPic1.BackColor = System.Drawing.Color.Transparent;
            this.PlayerPic1.Enabled = false;
            this.PlayerPic1.Image = global::Snakes_and_Ladders.Properties.Resources.player_1;
            this.PlayerPic1.Location = new System.Drawing.Point(38, 257);
            this.PlayerPic1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.PlayerPic1.Name = "PlayerPic1";
            this.PlayerPic1.Size = new System.Drawing.Size(25, 26);
            this.PlayerPic1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.PlayerPic1.TabIndex = 74;
            this.PlayerPic1.TabStop = false;
            // 
            // PlayerPic4
            // 
            this.PlayerPic4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PlayerPic4.BackColor = System.Drawing.Color.Transparent;
            this.PlayerPic4.Enabled = false;
            this.PlayerPic4.Image = global::Snakes_and_Ladders.Properties.Resources.player_4;
            this.PlayerPic4.Location = new System.Drawing.Point(418, 257);
            this.PlayerPic4.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.PlayerPic4.Name = "PlayerPic4";
            this.PlayerPic4.Size = new System.Drawing.Size(25, 26);
            this.PlayerPic4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.PlayerPic4.TabIndex = 79;
            this.PlayerPic4.TabStop = false;
            // 
            // PlayerPic3
            // 
            this.PlayerPic3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PlayerPic3.BackColor = System.Drawing.Color.Transparent;
            this.PlayerPic3.Enabled = false;
            this.PlayerPic3.Image = global::Snakes_and_Ladders.Properties.Resources.player_3;
            this.PlayerPic3.Location = new System.Drawing.Point(292, 257);
            this.PlayerPic3.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.PlayerPic3.Name = "PlayerPic3";
            this.PlayerPic3.Size = new System.Drawing.Size(25, 26);
            this.PlayerPic3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.PlayerPic3.TabIndex = 78;
            this.PlayerPic3.TabStop = false;
            // 
            // PlayerPic2
            // 
            this.PlayerPic2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PlayerPic2.BackColor = System.Drawing.Color.Transparent;
            this.PlayerPic2.Enabled = false;
            this.PlayerPic2.Image = global::Snakes_and_Ladders.Properties.Resources.player_2;
            this.PlayerPic2.Location = new System.Drawing.Point(166, 257);
            this.PlayerPic2.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.PlayerPic2.Name = "PlayerPic2";
            this.PlayerPic2.Size = new System.Drawing.Size(25, 26);
            this.PlayerPic2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.PlayerPic2.TabIndex = 77;
            this.PlayerPic2.TabStop = false;
            // 
            // StartUpForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(574, 310);
            this.Controls.Add(this.PlayerPic4);
            this.Controls.Add(this.PlayerPic3);
            this.Controls.Add(this.PlayerPic2);
            this.Controls.Add(this.PlayerPic1);
            this.Controls.Add(this.player4GB);
            this.Controls.Add(this.player3GB);
            this.Controls.Add(this.player2BG);
            this.Controls.Add(this.player1BG);
            this.Controls.Add(this.options);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericOfPlayers);
            this.Controls.Add(this.ButtonBegin);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "StartUpForm";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Settings";
            ((System.ComponentModel.ISupportInitialize)(this.numericOfPlayers)).EndInit();
            this.player1BG.ResumeLayout(false);
            this.player1BG.PerformLayout();
            this.player2BG.ResumeLayout(false);
            this.player2BG.PerformLayout();
            this.player3GB.ResumeLayout(false);
            this.player3GB.PerformLayout();
            this.player4GB.ResumeLayout(false);
            this.player4GB.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlayerPic2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ButtonBegin;
        private System.Windows.Forms.NumericUpDown numericOfPlayers;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label options;
        private System.Windows.Forms.GroupBox player1BG;
        private System.Windows.Forms.TextBox player1name;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox player2BG;
        private System.Windows.Forms.TextBox player2name;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox player3GB;
        private System.Windows.Forms.TextBox player3name;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox player4GB;
        private System.Windows.Forms.Button player4imageButton;
        private System.Windows.Forms.TextBox player4name;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button player1imageButton;
        private System.Windows.Forms.Button player2imageButton;
        private System.Windows.Forms.Button player3imageButton;
        private System.Windows.Forms.PictureBox PlayerPic1;
        private System.Windows.Forms.PictureBox PlayerPic4;
        private System.Windows.Forms.PictureBox PlayerPic3;
        private System.Windows.Forms.PictureBox PlayerPic2;
        private System.Windows.Forms.SaveFileDialog images;
    }
}