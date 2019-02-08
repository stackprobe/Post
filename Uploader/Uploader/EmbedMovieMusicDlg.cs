using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Uploader
{
	public partial class EmbedMovieMusicDlg : Form
	{
		public EmbedMovieMusicDlg()
		{
			InitializeComponent();
		}

		private void EmbedMovieMusicDlg_Load(object sender, EventArgs e)
		{
			// noop
		}

		private void EmbedMovieMusicDlg_Shown(object sender, EventArgs e)
		{
			this.LoadData();
			this.UpdateUi();
		}

		private void EmbedMovieMusicDlg_FormClosing(object sender, FormClosingEventArgs e)
		{
			// noop
		}

		private void EmbedMovieMusicDlg_FormClosed(object sender, FormClosedEventArgs e)
		{
			this.SaveData();
		}

		private void LoadData()
		{
			this.EmbedMovieFlag.Checked = Gnd.I.EmbedMovieFlag;
			this.MovieExts.Text = Gnd.I.MovieExts;
			this.EmbedMusicFlag.Checked = Gnd.I.EmbedMusicFlag;
			this.MusicExts.Text = Gnd.I.MusicExts;
		}

		private void SaveData()
		{
			Gnd.I.EmbedMovieFlag = this.EmbedMovieFlag.Checked;
			Gnd.I.MovieExts = this.MovieExts.Text;
			Gnd.I.EmbedMusicFlag = this.EmbedMusicFlag.Checked;
			Gnd.I.MusicExts = this.MusicExts.Text;
		}

		private void UpdateUi()
		{
			{
				bool flag = this.EmbedMovieFlag.Checked;

				this.MovieExtsLabel.Enabled = flag;
				this.MovieExts.Enabled = flag;
			}

			{
				bool flag = this.EmbedMusicFlag.Checked;

				this.MusicExtsLabel.Enabled = flag;
				this.MusicExts.Enabled = flag;
			}
		}

		private void EmbedMovieFlag_CheckedChanged(object sender, EventArgs e)
		{
			this.UpdateUi();
		}

		private void EmbedMusicFlag_CheckedChanged(object sender, EventArgs e)
		{
			this.UpdateUi();
		}
	}
}
