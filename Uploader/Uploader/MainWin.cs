using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace Uploader
{
	public partial class MainWin : Form
	{
		public MainWin()
		{
			InitializeComponent();
		}

		private void MainWin_Load(object sender, EventArgs e)
		{
			// noop
		}

		private bool ActivatedFlag;

		private void MainWin_Activated(object sender, EventArgs e)
		{
			if (this.ActivatedFlag)
				return;

			this.ActivatedFlag = true;
			Gnd.I.LoadConfig();
			Gnd.I.HTTProc.開始();
			this.UpdateUi();
			this.MT_Enabled = true;
		}

		private void MainWin_FormClosed(object sender, FormClosedEventArgs e)
		{
			this.MT_Enabled = false;
			//this.Status.Text = "終了しています...";
			Gnd.I.HTTProc.停止();
			Gnd.I.SaveConfig();
		}

		private void UpdateUi()
		{
			if (Gnd.I.HTTProc.Is開始())
			{
				this.Status.Text = "サーバーは稼動中です";
				this.Status.Enabled = true;

				this.再開SToolStripMenuItem.Enabled = false;
				this.一時停止TToolStripMenuItem.Enabled = true;
			}
			else
			{
				this.Status.Text = "サーバーは停止しています";
				this.Status.Enabled = false;

				this.再開SToolStripMenuItem.Enabled = true;
				this.一時停止TToolStripMenuItem.Enabled = false;
			}
		}

		private void 終了XToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private bool MT_Enabled;
		private bool MT_Busy;
		private long MT_Count;

		private void MainTimer_Tick(object sender, EventArgs e)
		{
			if (this.MT_Enabled == false)
				return;

			if (this.MT_Busy)
				return;

			this.MT_Busy = true;

			try
			{
				this.UpdateUi();

				if (this.MT_Count % 100 == 0)
				{
					GC.Collect();
				}
			}
			catch (Exception ex)
			{
				this.MT_Enabled = false;
				throw ex;
			}
			finally
			{
				this.MT_Busy = false;
				this.MT_Count++;
			}
		}

		private void 再開SToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Gnd.I.HTTProc.開始();
			this.UpdateUi();
		}

		private void 一時停止TToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Gnd.I.HTTProc.停止();
			this.UpdateUi();
		}

		private void 設定SToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.MT_Enabled = false;

			bool htt開始ed = Gnd.I.HTTProc.Is開始();
			Gnd.I.HTTProc.停止();

			this.Visible = false;

			using (Form f = new EditWin())
			{
				f.ShowDialog();
			}
			this.Visible = true;

			if (htt開始ed)
				Gnd.I.HTTProc.開始();

			this.MT_Enabled = true;

			this.UpdateUi();
		}

		private void Browse(string url)
		{
			try
			{
				ProcessStartInfo psi = new ProcessStartInfo();
				psi.FileName = url;
				Process.Start(psi);
			}
			catch (Exception e)
			{
				MessageBox.Show(
					"[Browse]\n" +
					"url=" + url + "\n" + e,
					"URLまたはフォルダが開けません",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
					);
			}
		}

		private void ブラウザを開くToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Browse("http://" + "localhost:" + Gnd.I.GetPortNo() + "/");
		}

		private void アップロード先フォルダを開くToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Gnd.I.LoadData();
			this.Browse(Gnd.I.UploadDir);
		}
	}
}
