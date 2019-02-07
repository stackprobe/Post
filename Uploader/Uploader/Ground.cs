using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Uploader
{
	public class Gnd
	{
		public static Gnd I = new Gnd();

		private Gnd()
		{ }

		public readonly string HTT_APP_UUID = "{1a7b4af5-cde5-4efd-aeab-35cdb9ad3c38}";

		public string DAT_FILE { get { return "Uploader.dat"; } }
		public readonly string PUTFILE_DATA_FILE = "PutFile.dat";
		public readonly string DOCROOT_FILE = "DocRoot.dat";

		public readonly int DEFAULT_PORTNO = 80;
		public readonly int DEFAULT_UPLOADEDFILENUMMAX = 5000;
		public readonly long DEFAULT_UPLOADDIRSIZEMAX = 9220000000000000000;
		public readonly long DEFAULT_UPLOADDISKFREEMIN = 3000000000;
		public readonly string DEFAULT_UPLOADDIR = "upload";
		public readonly long DEFAULT_SHOWEDIMAGETOTALSIZEMAX = 30000000;
		public readonly string DEFAULT_IMAGEEXTS = "bmp.gif.jpg.jpeg.png";
		public readonly string DEFAULT_MOVIEEXTS = "avi.mp4.mpeg.mpg.webm";
		public readonly string DEFAULT_MUSICEXTS = "mid.midi.mp3.wav.wma";

		public readonly string LANG_E = "E";
		public readonly string LANG_J = "J";

		public HTTProc HTTProc = new HTTProc();

		public enum ShowConsoleMode_e
		{
			HIDE,
			SHOW_MIN,
			SHOW_NORMAL,
		};

		public int PortNo = -1;
		public ShowConsoleMode_e ShowConsoleMode = ShowConsoleMode_e.HIDE; // 隠しモード

		public void LoadConfig()
		{
			this.PortNo = DEFAULT_PORTNO;

			try
			{
				string[] lines = File.ReadAllLines(this.DAT_FILE, Tools.ENCODING_SJIS);
				int c = 0;

				// ---- load data ----

				this.PortNo = (int)Tools.ParseLong(lines[c++], 1, 65535, Gnd.I.DEFAULT_PORTNO);
				this.ShowConsoleMode = (ShowConsoleMode_e)Tools.ParseLong(lines[c++], 0, 2, 0);

				// ----
			}
			catch
			{ }
		}

		public void SaveConfig()
		{
			try
			{
				List<string> lines = new List<string>();

				// ---- save data ----

				lines.Add("" + this.PortNo);
				lines.Add("" + (int)this.ShowConsoleMode);

				// ----

				File.WriteAllLines(this.DAT_FILE, lines, Tools.ENCODING_SJIS);
			}
			catch
			{ }
		}

		public int GetPortNo()
		{
			this.LoadConfig();
			return this.PortNo;
		}

		public void SetPortNo(int portNo)
		{
			this.PortNo = portNo;
			this.SaveConfig();
		}

		public int UploadedFileNumMax;
		public long UploadDirSizeMax;
		public long UploadDiskFreeMin;
		public string UploadDir;
		public string IndexFormatFile;
		public string ResponseHtmlFile;
		public long ShowedImageTotalSizeMax;
		public bool ShowImageFlag;
		public string ImageExts;
		public string DateLang;
		public bool ShowDeleteButtonFlag;
		public string Password;
		public bool NoOverwriteFlag;
		public bool ShowDownloadLinkFlag;
		public int SortOrder;
		public bool NoUpFaviconFlag;
		public bool EmbedMovieFlag;
		public string MovieExts;
		public bool EmbedMusicFlag;
		public string MusicExts;

		public void LoadDataDefault()
		{
			this.UploadedFileNumMax = Gnd.I.DEFAULT_UPLOADEDFILENUMMAX;
			this.UploadDirSizeMax = Gnd.I.DEFAULT_UPLOADDIRSIZEMAX;
			this.UploadDiskFreeMin = Gnd.I.DEFAULT_UPLOADDISKFREEMIN;
			this.UploadDir = Gnd.I.DEFAULT_UPLOADDIR;
			this.IndexFormatFile = "template\\index.htm.txt";
			this.ResponseHtmlFile = "template\\uploaded.htm.txt";
			this.ShowedImageTotalSizeMax = Gnd.I.DEFAULT_SHOWEDIMAGETOTALSIZEMAX;
			this.ShowImageFlag = true;
			this.ImageExts = Gnd.I.DEFAULT_IMAGEEXTS;
			this.DateLang = Gnd.I.LANG_J;
			this.ShowDeleteButtonFlag = false;
			this.Password = "";
			this.NoOverwriteFlag = false;
			this.ShowDownloadLinkFlag = false;
			this.SortOrder = 0;
			this.NoUpFaviconFlag = false;
			this.EmbedMovieFlag = true;
			this.MovieExts = Gnd.I.DEFAULT_MOVIEEXTS;
			this.EmbedMusicFlag = true;
			this.MusicExts = Gnd.I.DEFAULT_MUSICEXTS;
		}

		public void LoadData()
		{
			this.LoadDataDefault();

			try
			{
				string[] lines = File.ReadAllLines(Gnd.I.PUTFILE_DATA_FILE, Encoding.GetEncoding(932));
				int i = 0;

				// ---- load data ----

				this.UploadedFileNumMax = (int)Tools.ParseLong(lines[i++], 1, int.MaxValue, Gnd.I.DEFAULT_UPLOADEDFILENUMMAX);
				this.UploadDirSizeMax = Tools.ParseLong(lines[i++], 0, long.MaxValue, Gnd.I.DEFAULT_UPLOADDIRSIZEMAX);
				this.UploadDiskFreeMin = Tools.ParseLong(lines[i++], 0, long.MaxValue, Gnd.I.DEFAULT_UPLOADDISKFREEMIN);
				this.UploadDir = lines[i++];
				this.IndexFormatFile = lines[i++];
				this.ResponseHtmlFile = lines[i++];
				this.ShowedImageTotalSizeMax = Tools.ParseLong(lines[i++], 0, long.MaxValue, Gnd.I.DEFAULT_SHOWEDIMAGETOTALSIZEMAX);

				if (this.ShowedImageTotalSizeMax == 0)
				{
					this.ShowedImageTotalSizeMax = Gnd.I.DEFAULT_SHOWEDIMAGETOTALSIZEMAX;
					this.ShowImageFlag = false;
				}
				else
					this.ShowImageFlag = true;

				this.ImageExts = lines[i++];
				this.DateLang = lines[i++];
				this.ShowDeleteButtonFlag = Tools.ParseLong(lines[i++], 0, 1, 0) == 1;
				this.Password = lines[i++];
				this.NoOverwriteFlag = Tools.ParseLong(lines[i++], 0, 1, 0) == 1;
				this.ShowDownloadLinkFlag = Tools.ParseLong(lines[i++], 0, 1, 0) == 1;
				this.SortOrder = (int)Tools.ParseLong(lines[i++], 0, int.MaxValue, 0);
				this.NoUpFaviconFlag = Tools.ParseLong(lines[i++], 0, 1, 0) == 1;
				this.EmbedMovieFlag = Tools.ParseLong(lines[i++], 0, 1, 0) == 1;
				this.MovieExts = lines[i++];
				this.EmbedMusicFlag = Tools.ParseLong(lines[i++], 0, 1, 0) == 1;
				this.MusicExts = lines[i++];

				// ----
			}
			catch
			{
				//this.LoadDataDefault();
			}
		}

		public void SaveData()
		{
			try
			{
				List<string> lines = new List<string>();

				// ---- save data ----

				lines.Add("" + Tools.RangeLong(this.UploadedFileNumMax, 1, int.MaxValue));
				lines.Add("" + Tools.RangeLong(this.UploadDirSizeMax, 0, long.MaxValue));
				lines.Add("" + Tools.RangeLong(this.UploadDiskFreeMin, 0, long.MaxValue));
				lines.Add("" + this.UploadDir);
				lines.Add("" + this.IndexFormatFile);
				lines.Add("" + this.ResponseHtmlFile);
				lines.Add("" + Tools.RangeLong(
					this.ShowImageFlag ? this.ShowedImageTotalSizeMax : 0,
					0,
					long.MaxValue
					));
				lines.Add("" + this.ImageExts);
				lines.Add("" + this.DateLang);
				lines.Add("" + (this.ShowDeleteButtonFlag ? 1 : 0));
				lines.Add("" + this.Password);
				lines.Add("" + (this.NoOverwriteFlag ? 1 : 0));
				lines.Add("" + (this.ShowDownloadLinkFlag ? 1 : 0));
				lines.Add("" + this.SortOrder);
				lines.Add("" + (this.NoUpFaviconFlag ? 1 : 0));
				lines.Add("" + (this.EmbedMovieFlag ? 1 : 0));
				lines.Add("" + this.MovieExts);
				lines.Add("" + (this.EmbedMusicFlag ? 1 : 0));
				lines.Add("" + this.MusicExts);

				// ----

				File.WriteAllLines(Gnd.I.PUTFILE_DATA_FILE, lines.ToArray(), Encoding.GetEncoding(932));

				lines.Clear();
				lines.Add("default " + this.UploadDir);

				File.WriteAllLines(Gnd.I.DOCROOT_FILE, lines.ToArray(), Encoding.GetEncoding(932));
			}
			catch
			{ }
		}

		public bool Is初回起動()
		{
			return File.Exists(DAT_FILE) == false; // ? SaveConfig()を1度も実行していない。
		}
	}
}
