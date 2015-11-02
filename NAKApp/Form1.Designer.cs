namespace NAKApp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.axNAKCore1 = new AxNAKCoreLib.AxNAKCore();
            ((System.ComponentModel.ISupportInitialize)(this.axNAKCore1)).BeginInit();
            this.SuspendLayout();
            // 
            // axNAKCore1
            // 
            this.axNAKCore1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.axNAKCore1.Enabled = true;
            this.axNAKCore1.Location = new System.Drawing.Point(0, 0);
            this.axNAKCore1.Name = "axNAKCore1";
            this.axNAKCore1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axNAKCore1.OcxState")));
            this.axNAKCore1.Size = new System.Drawing.Size(282, 253);
            this.axNAKCore1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 253);
            this.Controls.Add(this.axNAKCore1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.axNAKCore1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private AxNAKCoreLib.AxNAKCore axNAKCore1;
    }
}