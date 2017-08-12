namespace Uploader
{
	partial class MainWin
	{
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWin));
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.アプリケーションAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.再開SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.一時停止TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.終了XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.設定Mnu = new System.Windows.Forms.ToolStripMenuItem();
			this.設定SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.toolStripDropDownButton1 = new System.Windows.Forms.ToolStripDropDownButton();
			this.アップロード先フォルダを開くToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.ブラウザを開くToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.Status = new System.Windows.Forms.Label();
			this.MainTimer = new System.Windows.Forms.Timer(this.components);
			this.menuStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.アプリケーションAToolStripMenuItem,
            this.設定Mnu});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(324, 26);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// アプリケーションAToolStripMenuItem
			// 
			this.アプリケーションAToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.再開SToolStripMenuItem,
            this.一時停止TToolStripMenuItem,
            this.toolStripMenuItem1,
            this.終了XToolStripMenuItem});
			this.アプリケーションAToolStripMenuItem.Name = "アプリケーションAToolStripMenuItem";
			this.アプリケーションAToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
			this.アプリケーションAToolStripMenuItem.Text = "アプリケーション(&A)";
			// 
			// 再開SToolStripMenuItem
			// 
			this.再開SToolStripMenuItem.Name = "再開SToolStripMenuItem";
			this.再開SToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.再開SToolStripMenuItem.Text = "開始(&S)";
			this.再開SToolStripMenuItem.Click += new System.EventHandler(this.再開SToolStripMenuItem_Click);
			// 
			// 一時停止TToolStripMenuItem
			// 
			this.一時停止TToolStripMenuItem.Name = "一時停止TToolStripMenuItem";
			this.一時停止TToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.一時停止TToolStripMenuItem.Text = "停止(&T)";
			this.一時停止TToolStripMenuItem.Click += new System.EventHandler(this.一時停止TToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(149, 6);
			// 
			// 終了XToolStripMenuItem
			// 
			this.終了XToolStripMenuItem.Name = "終了XToolStripMenuItem";
			this.終了XToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.終了XToolStripMenuItem.Text = "終了(&X)";
			this.終了XToolStripMenuItem.Click += new System.EventHandler(this.終了XToolStripMenuItem_Click);
			// 
			// 設定Mnu
			// 
			this.設定Mnu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.設定SToolStripMenuItem});
			this.設定Mnu.Name = "設定Mnu";
			this.設定Mnu.Size = new System.Drawing.Size(62, 22);
			this.設定Mnu.Text = "設定(&S)";
			// 
			// 設定SToolStripMenuItem
			// 
			this.設定SToolStripMenuItem.Name = "設定SToolStripMenuItem";
			this.設定SToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
			this.設定SToolStripMenuItem.Text = "設定(&S)";
			this.設定SToolStripMenuItem.Click += new System.EventHandler(this.設定SToolStripMenuItem_Click);
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripDropDownButton1});
			this.statusStrip1.Location = new System.Drawing.Point(0, 105);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(324, 22);
			this.statusStrip1.SizingGrip = false;
			this.statusStrip1.TabIndex = 1;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// toolStripDropDownButton1
			// 
			this.toolStripDropDownButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripDropDownButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.アップロード先フォルダを開くToolStripMenuItem,
            this.ブラウザを開くToolStripMenuItem});
			this.toolStripDropDownButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripDropDownButton1.Image")));
			this.toolStripDropDownButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripDropDownButton1.Name = "toolStripDropDownButton1";
			this.toolStripDropDownButton1.Size = new System.Drawing.Size(29, 20);
			this.toolStripDropDownButton1.Text = "toolStripDropDownButton1";
			// 
			// アップロード先フォルダを開くToolStripMenuItem
			// 
			this.アップロード先フォルダを開くToolStripMenuItem.Name = "アップロード先フォルダを開くToolStripMenuItem";
			this.アップロード先フォルダを開くToolStripMenuItem.Size = new System.Drawing.Size(244, 22);
			this.アップロード先フォルダを開くToolStripMenuItem.Text = "アップロード先フォルダを開く";
			this.アップロード先フォルダを開くToolStripMenuItem.Click += new System.EventHandler(this.アップロード先フォルダを開くToolStripMenuItem_Click);
			// 
			// ブラウザを開くToolStripMenuItem
			// 
			this.ブラウザを開くToolStripMenuItem.Name = "ブラウザを開くToolStripMenuItem";
			this.ブラウザを開くToolStripMenuItem.Size = new System.Drawing.Size(244, 22);
			this.ブラウザを開くToolStripMenuItem.Text = "ブラウザを開く";
			this.ブラウザを開くToolStripMenuItem.Click += new System.EventHandler(this.ブラウザを開くToolStripMenuItem_Click);
			// 
			// Status
			// 
			this.Status.AutoSize = true;
			this.Status.Font = new System.Drawing.Font("メイリオ", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.Status.Location = new System.Drawing.Point(36, 52);
			this.Status.Name = "Status";
			this.Status.Size = new System.Drawing.Size(164, 28);
			this.Status.TabIndex = 2;
			this.Status.Text = "現在のステータス";
			// 
			// MainTimer
			// 
			this.MainTimer.Enabled = true;
			this.MainTimer.Interval = 2000;
			this.MainTimer.Tick += new System.EventHandler(this.MainTimer_Tick);
			// 
			// MainWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(324, 127);
			this.Controls.Add(this.Status);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.menuStrip1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MainMenuStrip = this.menuStrip1;
			this.MaximizeBox = false;
			this.Name = "MainWin";
			this.Text = "Uploader";
			this.Activated += new System.EventHandler(this.MainWin_Activated);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWin_FormClosed);
			this.Load += new System.EventHandler(this.MainWin_Load);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem アプリケーションAToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem 設定Mnu;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.ToolStripMenuItem 再開SToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem 一時停止TToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem 終了XToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem 設定SToolStripMenuItem;
		private System.Windows.Forms.Label Status;
		private System.Windows.Forms.Timer MainTimer;
		private System.Windows.Forms.ToolStripDropDownButton toolStripDropDownButton1;
		private System.Windows.Forms.ToolStripMenuItem ブラウザを開くToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem アップロード先フォルダを開くToolStripMenuItem;
	}
}

