using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DanmakuSimulator {
    public partial class Form1 : Form {

        void DrawOne(Graphics g, int x, int y) {
            //             Point ZeroPoint = new Point(this.ClientSize.Width / 2, this.ClientSize.Height / 2);
            //             Point ThisPoint = new Point(ZeroPoint.X + x, ZeroPoint.Y + y);
            //             System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.White);//画刷
            //             int RSize = 5;
            //             g.FillEllipse(myBrush, new Rectangle(ThisPoint.X - RSize, ThisPoint.Y - RSize, RSize * 2, RSize * 2));

            g.TranslateTransform(this.ClientSize.Width / 2, this.ClientSize.Height / 2);
            int RSize = 5;
            SolidBrush myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.White);
            g.FillEllipse(myBrush, new Rectangle(x - RSize, y - RSize, RSize * 2, RSize * 2));
            g.ResetTransform();
        }

        private Timer timer;

        public Form1() {
            InitializeComponent();

            timer = new Timer();
            timer.Tick += new EventHandler(timer1_Tick);
            timer.Interval = 16;
            timer.Enabled = true;
            this.DoubleBuffered = true;
        }

        private void Form1_Load(object sender, EventArgs e) {

        }

        int i = 0;

        private void timer1_Tick(object sender, EventArgs e) {
            Graphics g = this.CreateGraphics();
            g.Clear(Color.Black);
            DrawOne(g, ++i, ++i);

        }

    }
}
