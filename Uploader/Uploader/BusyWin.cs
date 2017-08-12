using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Security.Permissions;

namespace Uploader
{
	/// <summary>
	/// 使い方
	/// new BusyWin().Perform(runner);
	/// </summary>
	public partial class BusyWin : Form
	{
		// ---- ALT_F4 抑止 ----

		[SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
		protected override void WndProc(ref Message m)
		{
			const int WM_SYSCOMMAND = 0x112;
			const long SC_CLOSE = 0xF060L;

			if (m.Msg == WM_SYSCOMMAND && (m.WParam.ToInt64() & 0xFFF0L) == SC_CLOSE)
			{
				return;
			}
			base.WndProc(ref m);
		}

		// ----

		public BusyWin()
		{
			InitializeComponent();
		}

		private Thread Runner;

		private void BusyWin_Load(object sender, EventArgs e)
		{
			// noop
		}

		public void DoStart(Thread runner)
		{
			this.Runner = runner;
			this.Runner.Start();
		}

		private bool ActivatedFlag;

		private void BusyWin_Activated(object sender, EventArgs e)
		{
			if (this.ActivatedFlag)
				return;

			this.ActivatedFlag = true;
			this.MT_Enabled = true;
		}

		private bool MT_Enabled;
		private bool MT_Busy;
		private long MT_Count;

		private void MainTimer_Tick(object sender, EventArgs e)
		{
			if (this.MT_Enabled == false || this.MT_Busy)
				return;

			this.MT_Busy = true;

			try
			{
				if (this.MT_Count < 5)
					return;

				if (this.Runner.IsAlive == false)
				{
					this.MT_Enabled = false;
					this.Close();
				}
			}
			catch (Exception ex)
			{
				this.MT_Enabled = false;
				throw ex;
			}
			finally
			{
				this.MT_Count++;
				this.MT_Busy = false;
			}
		}
	}
}
