using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Danmaker {

	public partial class Form1 : Form {
		Looper timeController;
		Graphics g;
		Graphics surfg;
		Bitmap surface;

		public Form1() {
			InitializeComponent();
			surface = new Bitmap(MainBox.Size.Width, MainBox.Size.Height);
			surfg = Graphics.FromImage(surface);
			Init();
			this.DoubleBuffered = true;
			Timer timer = new Timer();
			timer.Tick += Timer_Counter;
			timer.Interval = 1000;
			timer.Enabled = true;
			timeController = new Looper(GameLoop);
			g = MainBox.CreateGraphics();
		}

		private void Timer_Counter(object sender, EventArgs e) {
			this.Text = "FPS: " + counter.ToString();
			counter = 0;
		}

		BaseBallet bb;

		void Init() {
			bb = new BaseBallet(new Vector2(225, 225), new Vector2(1, 1), new Vector2(0, 0));
		}

		void DrawAxis(Graphics g, Point center) {
			g.DrawLine(Pens.Aqua, MainBox.Width / 2, 0, MainBox.Width / 2, MainBox.Height);
			g.DrawLine(Pens.Aqua, 0, MainBox.Height / 2, MainBox.Width, MainBox.Height / 2);
		}

		void DrawPoint(Graphics g, float x, float y, float r = 2) {
			g.FillEllipse(Brushes.Red, x - r, y - r, r * 2, r * 2);
		}

		void Graph() {
			//DrawAxis(surfg, new Point(225, 225));
			//==
			Vector2 v = bb.GetPosition();
			DrawPoint(surfg, v.X, v.Y);
			//==
			g.DrawImage(surface, 0, 0);
			//6g.FillEllipse(Brushes.White, 0, 0, 10, 10);
		}

		bool start = false;

		void GameLoop(double ElapsedTime) {
			if(start)
				Graph();
			counter++;
		}

		int counter = 0;

		private void label1_Click(object sender, EventArgs e) {
			
		}

		private void button1_Click(object sender, EventArgs e) {
			start = false;
		}

		private void button2_Click(object sender, EventArgs e) {
			start = true;
			surfg.Clear(Color.Black);
		}

		private void button3_Click(object sender, EventArgs e) {
			start = false;
			BalletDescriber tmp = bb.Anim[0];
			tmp.Speed = new Vector2((float)SX.Value / 10.0f, (float)SY.Value / 10.0f);
			tmp.SpeedInc = new Vector2((float)SIX.Value / 10.0f, (float)SIY.Value / 10.0f);
			tmp.RotationInc = (float)R.Value / 10.0f;
			bb.Position = new Vector2(PX.Value, PY.Value);
			bb.Anim[0] = tmp;
		}

		private void PX_Scroll(object sender, EventArgs e) {
			PXT.Text = PX.Value.ToString();
		}

		private void PY_Scroll(object sender, EventArgs e) {
			PYT.Text = PY.Value.ToString();
		}

		private void SX_Scroll(object sender, EventArgs e) {
			SXT.Text = (SX.Value / 10.0f).ToString();
		}

		private void SY_Scroll(object sender, EventArgs e) {
			SYT.Text = (SY.Value / 10.0f).ToString();
		}

		private void SIX_Scroll(object sender, EventArgs e) {
			SIXT.Text = (SIX.Value / 10.0f).ToString();
		}

		private void SIY_Scroll(object sender, EventArgs e) {
			SIYT.Text = (SIY.Value / 10.0f).ToString();
		}

		private void R_Scroll(object sender, EventArgs e) {
			RT.Text = (R.Value / 10.0f).ToString();
		}

		private void PXT_TextChanged(object sender, EventArgs e) {
			PX.Value = int.Parse(PXT.Text);
		}

		private void SXT_TextChanged(object sender, EventArgs e) {
			SX.Value = (int)(float.Parse(SXT.Text) * 10.0f);
		}

		private void SIXT_TextChanged(object sender, EventArgs e) {
			SIX.Value = (int)(float.Parse(SIXT.Text) * 10.0f);
		}

		private void RT_TextChanged(object sender, EventArgs e) {
			R.Value = (int)(float.Parse(RT.Text) * 10.0f);
		}

		private void SIYT_TextChanged(object sender, EventArgs e) {
			SIY.Value = (int)(float.Parse(SIYT.Text) * 10.0f);
		}

		private void SYT_TextChanged(object sender, EventArgs e) {
			SY.Value = (int)(float.Parse(SYT.Text) * 10.0f);
		}

		private void PYT_TextChanged(object sender, EventArgs e) {
			PY.Value = int.Parse(PYT.Text);
		}
	}

	public class PreciseTimer {
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("kernel32")]
		private static extern bool QueryPerformanceFrequency(ref long PerformanceFrequency);
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("kernel32")]
		private static extern bool QueryPerformanceCounter(ref long PerformanceCounter);

		long _tickPerSecond = 0;
		long _previousElapsedTime = 0;

		public PreciseTimer() {
			QueryPerformanceFrequency(ref _tickPerSecond);
			GetElapsedTime();
		}
		public double GetElapsedTime() {
			long Time = 0;
			QueryPerformanceCounter(ref Time);
			double ElapsedTime = (double)(Time - _previousElapsedTime) / (double)_tickPerSecond;
			return ElapsedTime;
		}

		public void Reset() {
			long Time = 0;
			QueryPerformanceCounter(ref Time);
			double ElapsedTime = (double)(Time - _previousElapsedTime) / (double)_tickPerSecond;
			_previousElapsedTime = Time;
		}
	}

	public class Looper {
		[System.Security.SuppressUnmanagedCodeSecurity]
		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern bool PeekMessage(
	  out Message Msg,
	  IntPtr hWnd,
	  uint messageFilterMin,
	  uint messageFilterMax,
	  uint flags);

		PreciseTimer _preciseTimer = new PreciseTimer();
		public delegate void LoopCallBack(double ElapsedTime);
		LoopCallBack _loopCallBack;
		public Looper(LoopCallBack CallBack) {
			_loopCallBack = CallBack;
			Application.Idle += new EventHandler(OnApplicationEnterIdle);
		}
		private void OnApplicationEnterIdle(object sender, EventArgs e) {
			while (IsAppStillIdle())
				if (_preciseTimer.GetElapsedTime() >= 0.01667) {
					_loopCallBack(_preciseTimer.GetElapsedTime());
					_preciseTimer.Reset();
				}
		}
		private bool IsAppStillIdle() {
			Message Msg;
			return !PeekMessage(out Msg, IntPtr.Zero, 0, 0, 0);
		}
	}
}
