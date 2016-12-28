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
            Point ZeroPoint = new Point(this.ClientSize.Width / 2, this.ClientSize.Height / 2);
            Point ThisPoint = new Point(ZeroPoint.X + x, ZeroPoint.Y + y);
            System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.White);//画刷
            int RSize = 5;
            g.FillEllipse(myBrush, new Rectangle(ThisPoint.X - RSize, ThisPoint.Y - RSize, RSize * 2, RSize * 2));
        }

        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {

        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            Graphics g = this.CreateGraphics();
            g.Clear(Color.Black);

            DrawOne(g, 10, 10);
        }
    }
}
