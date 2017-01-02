namespace Danmaker {
	partial class Form1 {
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows 窗体设计器生成的代码

		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent() {
			this.MainBox = new System.Windows.Forms.PictureBox();
			this.PX = new System.Windows.Forms.TrackBar();
			this.button1 = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.PY = new System.Windows.Forms.TrackBar();
			this.label2 = new System.Windows.Forms.Label();
			this.SX = new System.Windows.Forms.TrackBar();
			this.SY = new System.Windows.Forms.TrackBar();
			this.label3 = new System.Windows.Forms.Label();
			this.SIX = new System.Windows.Forms.TrackBar();
			this.SIY = new System.Windows.Forms.TrackBar();
			this.R = new System.Windows.Forms.TrackBar();
			this.label4 = new System.Windows.Forms.Label();
			this.button2 = new System.Windows.Forms.Button();
			this.PXT = new System.Windows.Forms.TextBox();
			this.PYT = new System.Windows.Forms.TextBox();
			this.SXT = new System.Windows.Forms.TextBox();
			this.RT = new System.Windows.Forms.TextBox();
			this.SIXT = new System.Windows.Forms.TextBox();
			this.SYT = new System.Windows.Forms.TextBox();
			this.SIYT = new System.Windows.Forms.TextBox();
			this.button3 = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.MainBox)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.PX)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.PY)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.SX)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.SY)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.SIX)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.SIY)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.R)).BeginInit();
			this.SuspendLayout();
			// 
			// MainBox
			// 
			this.MainBox.Location = new System.Drawing.Point(11, 9);
			this.MainBox.Name = "MainBox";
			this.MainBox.Size = new System.Drawing.Size(450, 450);
			this.MainBox.TabIndex = 0;
			this.MainBox.TabStop = false;
			// 
			// PX
			// 
			this.PX.Location = new System.Drawing.Point(467, 26);
			this.PX.Maximum = 450;
			this.PX.Name = "PX";
			this.PX.Size = new System.Drawing.Size(215, 45);
			this.PX.TabIndex = 1;
			this.PX.Scroll += new System.EventHandler(this.PX_Scroll);
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(461, 419);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 2;
			this.button1.Text = "Clear";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(465, 11);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(53, 12);
			this.label1.TabIndex = 3;
			this.label1.Text = "Position";
			this.label1.Click += new System.EventHandler(this.label1_Click);
			// 
			// PY
			// 
			this.PY.Location = new System.Drawing.Point(743, 26);
			this.PY.Maximum = 450;
			this.PY.Name = "PY";
			this.PY.Size = new System.Drawing.Size(215, 45);
			this.PY.TabIndex = 4;
			this.PY.Scroll += new System.EventHandler(this.PY_Scroll);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(465, 59);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(35, 12);
			this.label2.TabIndex = 5;
			this.label2.Text = "Speed";
			// 
			// SX
			// 
			this.SX.Location = new System.Drawing.Point(467, 77);
			this.SX.Maximum = 100;
			this.SX.Name = "SX";
			this.SX.Size = new System.Drawing.Size(215, 45);
			this.SX.TabIndex = 6;
			this.SX.Scroll += new System.EventHandler(this.SX_Scroll);
			// 
			// SY
			// 
			this.SY.Location = new System.Drawing.Point(743, 77);
			this.SY.Maximum = 100;
			this.SY.Name = "SY";
			this.SY.Size = new System.Drawing.Size(215, 45);
			this.SY.TabIndex = 7;
			this.SY.Scroll += new System.EventHandler(this.SY_Scroll);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(465, 110);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(53, 12);
			this.label3.TabIndex = 8;
			this.label3.Text = "SpeedInc";
			// 
			// SIX
			// 
			this.SIX.Location = new System.Drawing.Point(467, 128);
			this.SIX.Maximum = 100;
			this.SIX.Name = "SIX";
			this.SIX.Size = new System.Drawing.Size(215, 45);
			this.SIX.TabIndex = 9;
			this.SIX.Scroll += new System.EventHandler(this.SIX_Scroll);
			// 
			// SIY
			// 
			this.SIY.Location = new System.Drawing.Point(743, 128);
			this.SIY.Maximum = 100;
			this.SIY.Name = "SIY";
			this.SIY.Size = new System.Drawing.Size(215, 45);
			this.SIY.TabIndex = 10;
			this.SIY.Scroll += new System.EventHandler(this.SIY_Scroll);
			// 
			// R
			// 
			this.R.Location = new System.Drawing.Point(467, 179);
			this.R.Maximum = 100;
			this.R.Name = "R";
			this.R.Size = new System.Drawing.Size(215, 45);
			this.R.TabIndex = 11;
			this.R.Scroll += new System.EventHandler(this.R_Scroll);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(465, 161);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(71, 12);
			this.label4.TabIndex = 12;
			this.label4.Text = "RotationInc";
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(542, 419);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 13;
			this.button2.Text = "Start";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// PXT
			// 
			this.PXT.Location = new System.Drawing.Point(689, 26);
			this.PXT.Name = "PXT";
			this.PXT.Size = new System.Drawing.Size(48, 21);
			this.PXT.TabIndex = 14;
			this.PXT.TextChanged += new System.EventHandler(this.PXT_TextChanged);
			// 
			// PYT
			// 
			this.PYT.Location = new System.Drawing.Point(964, 26);
			this.PYT.Name = "PYT";
			this.PYT.Size = new System.Drawing.Size(48, 21);
			this.PYT.TabIndex = 15;
			this.PYT.TextChanged += new System.EventHandler(this.PYT_TextChanged);
			// 
			// SXT
			// 
			this.SXT.Location = new System.Drawing.Point(688, 77);
			this.SXT.Name = "SXT";
			this.SXT.Size = new System.Drawing.Size(48, 21);
			this.SXT.TabIndex = 16;
			this.SXT.TextChanged += new System.EventHandler(this.SXT_TextChanged);
			// 
			// RT
			// 
			this.RT.Location = new System.Drawing.Point(688, 179);
			this.RT.Name = "RT";
			this.RT.Size = new System.Drawing.Size(48, 21);
			this.RT.TabIndex = 17;
			this.RT.TextChanged += new System.EventHandler(this.RT_TextChanged);
			// 
			// SIXT
			// 
			this.SIXT.Location = new System.Drawing.Point(688, 128);
			this.SIXT.Name = "SIXT";
			this.SIXT.Size = new System.Drawing.Size(48, 21);
			this.SIXT.TabIndex = 18;
			this.SIXT.TextChanged += new System.EventHandler(this.SIXT_TextChanged);
			// 
			// SYT
			// 
			this.SYT.Location = new System.Drawing.Point(964, 77);
			this.SYT.Name = "SYT";
			this.SYT.Size = new System.Drawing.Size(48, 21);
			this.SYT.TabIndex = 19;
			this.SYT.TextChanged += new System.EventHandler(this.SYT_TextChanged);
			// 
			// SIYT
			// 
			this.SIYT.Location = new System.Drawing.Point(964, 128);
			this.SIYT.Name = "SIYT";
			this.SIYT.Size = new System.Drawing.Size(48, 21);
			this.SIYT.TabIndex = 20;
			this.SIYT.TextChanged += new System.EventHandler(this.SIYT_TextChanged);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(623, 419);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(75, 23);
			this.button3.TabIndex = 21;
			this.button3.Text = "Set";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.ButtonShadow;
			this.ClientSize = new System.Drawing.Size(1061, 484);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.SIYT);
			this.Controls.Add(this.SYT);
			this.Controls.Add(this.SIXT);
			this.Controls.Add(this.RT);
			this.Controls.Add(this.SXT);
			this.Controls.Add(this.PYT);
			this.Controls.Add(this.PXT);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.R);
			this.Controls.Add(this.SIY);
			this.Controls.Add(this.SIX);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.SY);
			this.Controls.Add(this.SX);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.PY);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.PX);
			this.Controls.Add(this.MainBox);
			this.Name = "Form1";
			this.Text = "Form1";
			((System.ComponentModel.ISupportInitialize)(this.MainBox)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.PX)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.PY)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.SX)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.SY)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.SIX)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.SIY)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.R)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.PictureBox MainBox;
		private System.Windows.Forms.TrackBar PX;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TrackBar PY;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TrackBar SX;
		private System.Windows.Forms.TrackBar SY;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TrackBar SIX;
		private System.Windows.Forms.TrackBar SIY;
		private System.Windows.Forms.TrackBar R;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.TextBox PXT;
		private System.Windows.Forms.TextBox PYT;
		private System.Windows.Forms.TextBox SXT;
		private System.Windows.Forms.TextBox RT;
		private System.Windows.Forms.TextBox SIXT;
		private System.Windows.Forms.TextBox SYT;
		private System.Windows.Forms.TextBox SIYT;
		private System.Windows.Forms.Button button3;
	}
}

