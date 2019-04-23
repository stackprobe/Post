using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Uploader
{
	public partial class EditWin : Form
	{
		public EditWin()
		{
			InitializeComponent();

			{
				Color bc = this.PortNo.BackColor;

				this.UploadDir.BackColor = bc;
				//this.IndexFormatFile.BackColor = bc; // 項目を廃止した。
				//this.ResponseHtmlFile.BackColor = bc; // 項目を廃止した。
			}
		}

		private void LoadData()
		{
			this.PortNo.Text = "" + Gnd.I.GetPortNo();
			this.UploadDirSizeMax.Text = "" + Gnd.I.UploadDirSizeMax;
			this.UploadDiskFreeMin.Text = "" + Gnd.I.UploadDiskFreeMin;
			this.UploadedFileNumMax.Text = "" + Gnd.I.UploadedFileNumMax;

			this.UploadDir.Text = Gnd.I.UploadDir;
			//this.IndexFormatFile.Text = G.I.IndexFormatFile; // 項目を廃止した。
			//this.ResponseHtmlFile.Text = G.I.ResponseHtmlFile; // 項目を廃止した。

			this.ShowImageFlag.Checked = Gnd.I.ShowImageFlag;
			this.ShowedImageTotalSizeMax.Text = "" + Gnd.I.ShowedImageTotalSizeMax;
			this.ImageExts.Text = Gnd.I.ImageExts;

			this.DateLangJ.Checked = Gnd.I.DateLang == Gnd.I.LANG_J;
			this.ShowDeleteButtonFlag.Checked = Gnd.I.ShowDeleteButtonFlag;

			this.PasswordEnabled.Checked = Gnd.I.Password != "";
			this.Password.Text = Gnd.I.Password;
			this.NoOverwriteFlag.Checked = Gnd.I.NoOverwriteFlag;
			this.ShowDownloadLinkFlag.Checked = Gnd.I.ShowDownloadLinkFlag;
			this.NoUpFavicon.Checked = Gnd.I.NoUpFaviconFlag;

			try
			{
				this.SortOrder.SelectedIndex = Gnd.I.SortOrder;
			}
			catch
			{ }
		}

		private void SaveData()
		{
			Gnd.I.SetPortNo((int)Tools.ParseLong(this.PortNo.Text, 1, 65535, 80));
			Gnd.I.UploadDirSizeMax = Tools.ParseLong(
				this.UploadDirSizeMax.Text,
				0,
				long.MaxValue,
				Gnd.I.DEFAULT_UPLOADDIRSIZEMAX
				);
			Gnd.I.UploadDiskFreeMin = Tools.ParseLong(
				this.UploadDiskFreeMin.Text,
				0,
				long.MaxValue,
				Gnd.I.DEFAULT_UPLOADDISKFREEMIN
				);
			Gnd.I.UploadedFileNumMax = (int)Tools.ParseLong(
				this.UploadedFileNumMax.Text,
				1,
				int.MaxValue,
				Gnd.I.DEFAULT_UPLOADEDFILENUMMAX
				);

			Gnd.I.UploadDir = this.UploadDir.Text;
			//G.I.IndexFormatFile = this.IndexFormatFile.Text; // 項目を廃止した。
			//G.I.ResponseHtmlFile = this.ResponseHtmlFile.Text; // 項目を廃止した。

			Gnd.I.ShowImageFlag = this.ShowImageFlag.Checked;
			Gnd.I.ShowedImageTotalSizeMax = Tools.ParseLong(
				this.ShowedImageTotalSizeMax.Text,
				0,
				long.MaxValue,
				Gnd.I.DEFAULT_SHOWEDIMAGETOTALSIZEMAX
				);
			Gnd.I.ImageExts = Tools.ExtsFltr(this.ImageExts.Text);

			Gnd.I.DateLang = this.DateLangJ.Checked ? Gnd.I.LANG_J : Gnd.I.LANG_E;
			Gnd.I.ShowDeleteButtonFlag = this.ShowDeleteButtonFlag.Checked;

			Gnd.I.Password = this.PasswordEnabled.Checked ? this.Password.Text : "";
			Gnd.I.NoOverwriteFlag = this.NoOverwriteFlag.Checked;
			Gnd.I.ShowDownloadLinkFlag = this.ShowDownloadLinkFlag.Checked;
			Gnd.I.NoUpFaviconFlag = this.NoUpFavicon.Checked;

			Gnd.I.SortOrder = this.SortOrder.SelectedIndex;
		}

		private void EditWin_Load(object sender, EventArgs e)
		{
			Gnd.I.LoadData();
			this.LoadData();
			this.UpdateUi();
		}

		private void EditWin_Shown(object sender, EventArgs e)
		{
			Tools.PostShown(this);
		}

		private void EditWin_FormClosed(object sender, FormClosedEventArgs e)
		{
			this.SaveData();
			Gnd.I.SaveData();
		}

		private void UpdateUi()
		{
			{
				bool flag = this.ShowImageFlag.Checked;

				this.画像ラベル1.Enabled = flag;
				this.ShowedImageTotalSizeMax.Enabled = flag;
				this.画像ラベル1_1.Enabled = flag;
				this.画像ラベル2.Enabled = flag;
				this.ImageExts.Enabled = flag;
				this.ShowedImageTotalSizeMaxデフォルトBtn.Enabled = flag;

				this.Password.Enabled = this.PasswordEnabled.Checked;
			}
		}

		private void ShowImageFlag_CheckedChanged(object sender, EventArgs e)
		{
			this.UpdateUi();
		}

		private void リセットBtn_Click(object sender, EventArgs e)
		{
			Gnd.I.LoadData();
			this.LoadData();
			this.UpdateUi();
		}

		private void デフォルトBtn_Click(object sender, EventArgs e)
		{
			Gnd.I.LoadDataDefault();
			this.LoadData();
			this.PortNo.Text = "" + Gnd.I.DEFAULT_PORTNO;
			this.UpdateUi();
		}

		private void UploadDir_TextChanged(object sender, EventArgs e)
		{
			// noop
		}

		private void SelectDir(TextBox tb)
		{
			try
			{
				string homeDir = Directory.GetCurrentDirectory();
				string selDir;

				{
					string selPath = tb.Text;
					selPath = Path.GetFullPath(selPath);

					if (Directory.Exists(selPath))
						selDir = selPath;
					else
						selDir = homeDir;
				}

				if (SaveLoadDialogs.SelectFolder(ref selDir, "フォルダを選択して下さい。"))
				{
					{
						string selPath = selDir;

						if (selPath.StartsWith("\\\\"))
						{
							throw new Exception("ネットワークフォルダは使用できません");
							//selPath = "(ネットワークフォルダは使用できません)";
						}
						if (3 < homeDir.Length) // ? not root-dir
							if (selPath.StartsWith(homeDir + "\\", StringComparison.OrdinalIgnoreCase))
								selPath = selPath.Substring(homeDir.Length + 1);

						{
							string tmpPath = JString.ToJString(selPath, true, false, false, true, 0, 300);
							//tmpPath = tmpPath.Trim(); // moved

							if (tmpPath != selPath) throw new Exception("Shift_JISに変換出来ない文字を含むパスは使用できません");
							//if (tmpPath != selPath) selPath = "(Shift_JISに変換出来ない文字を含むパスは使用できません)";
							//selPath = tmpPath;
						}

						{
							string tmpPath = selPath.Trim();

							if (tmpPath != selPath)
								throw new Exception("空白の位置に問題があります");
						}

						if (selPath == "")
						{
							throw new Exception("空文字列は使用できません");
							//selPath = "(空文字列は使用できません)";
						}
						if (selPath == tb.Text) // ? 今設定されているフォルダを選択した。
							return;

						selDir = selPath;
					}

					if (MessageBox.Show(
						"新しい アップロード先フォルダ が選択されました。\n" +
						"\n" +
						"アップロード先フォルダ 内のファイル及びフォルダは、アップロードによる上書き、ディスクの空き領域確保 などの理由により、自動的に削除されることがあります。\n" +
						"\n" +
						"続行するには OK を押して下さい。",
						"アップロード先フォルダ変更の確認",
						MessageBoxButtons.OKCancel,
						MessageBoxIcon.Information
						) == DialogResult.OK
						)
					{
						tb.Text = selDir;
						tb.SelectAll();
					}
				}
			}
			catch (Exception e)
			{
				MessageBox.Show(
					"" + e,
					"フォルダ選択_失敗",
					MessageBoxButtons.OK,
					MessageBoxIcon.Warning
					);

				//tb.Text = Gnd.I.DEFAULT_UPLOADDIR;
			}
		}

		private void UploadDir_Click(object sender, EventArgs e)
		{
			this.SelectDir(this.UploadDir);
		}

		private void UploadDir_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == (char)Keys.Enter)
			{
				e.Handled = true;
				this.Close();
			}
			if (e.KeyChar == (char)Keys.Space)
			{
				e.Handled = true;
				this.SelectDir(this.UploadDir);
			}
		}

		private void UploadDirデフォルトBtn_Click(object sender, EventArgs e)
		{
			this.UploadDir.Text = Gnd.I.DEFAULT_UPLOADDIR;
		}

		private void KeyPressCommon(KeyPressEventArgs e)
		{
			if (e.KeyChar == (char)Keys.Enter)
			{
				e.Handled = true;
				this.Close();
			}
		}

		private void PortNo_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void UploadDirSizeMax_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void UploadDiskFreeMin_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void UploadedFileNumMax_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void ShowImageFlag_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void ShowedImageTotalSizeMax_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void ImageExts_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void UploadDirSizeMaxデフォルトBtn_Click(object sender, EventArgs e)
		{
			this.UploadDirSizeMax.Text = "" + Gnd.I.DEFAULT_UPLOADDIRSIZEMAX;
		}

		private void UploadDiskFreeMinデフォルトBtn_Click(object sender, EventArgs e)
		{
			this.UploadDiskFreeMin.Text = "" + Gnd.I.DEFAULT_UPLOADDISKFREEMIN;
		}

		private void UploadedFileNumMaxデフォルトBtn_Click(object sender, EventArgs e)
		{
			this.UploadedFileNumMax.Text = "" + Gnd.I.DEFAULT_UPLOADEDFILENUMMAX;
		}

		private void PasswordEnabled_CheckedChanged(object sender, EventArgs e)
		{
			this.UpdateUi();
		}

		private void Password_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.KeyPressCommon(e);
		}

		private void PortNoデフォルトBtn_Click(object sender, EventArgs e)
		{
			this.PortNo.Text = "" + Gnd.I.DEFAULT_PORTNO;
		}

		private void ShowedImageTotalSizeMaxデフォルトBtn_Click(object sender, EventArgs e)
		{
			this.ShowedImageTotalSizeMax.Text = "" + Gnd.I.DEFAULT_SHOWEDIMAGETOTALSIZEMAX;
			this.ImageExts.Text = Gnd.I.DEFAULT_IMAGEEXTS;
		}

		private void MovieMusicEmbedBtn_Click(object sender, EventArgs e)
		{
			this.Visible = false;

			using (EmbedMovieMusicDlg f = new EmbedMovieMusicDlg())
			{
				f.ShowDialog();
			}
			this.Visible = true;
		}
	}
}
