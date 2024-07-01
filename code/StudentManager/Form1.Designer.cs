namespace StudentManager
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            Status = new Label();
            statusLabel = new Label();
            addButton = new Button();
            clearButton = new Button();
            updateButton = new Button();
            serialOutput = new TextBox();
            dataStudent = new DataGridView();
            label3 = new Label();
            textBoxName = new TextBox();
            textBoxStudentID = new TextBox();
            label1 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataStudent).BeginInit();
            SuspendLayout();
            // 
            // Status
            // 
            Status.AutoSize = true;
            Status.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            Status.Location = new Point(26, 35);
            Status.Name = "Status";
            Status.Size = new Size(101, 37);
            Status.TabIndex = 0;
            Status.Text = "Status: ";
            // 
            // statusLabel
            // 
            statusLabel.AutoSize = true;
            statusLabel.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            statusLabel.ForeColor = Color.Red;
            statusLabel.Location = new Point(112, 35);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(247, 37);
            statusLabel.TabIndex = 1;
            statusLabel.Text = "Đang tìm Arduino...";
            // 
            // addButton
            // 
            addButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            addButton.Location = new Point(965, 27);
            addButton.Margin = new Padding(3, 4, 3, 4);
            addButton.Name = "addButton";
            addButton.Size = new Size(268, 53);
            addButton.TabIndex = 2;
            addButton.Text = "Thêm Sinh Viên";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // clearButton
            // 
            clearButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            clearButton.Location = new Point(34, 760);
            clearButton.Margin = new Padding(3, 4, 3, 4);
            clearButton.Name = "clearButton";
            clearButton.Size = new Size(155, 53);
            clearButton.TabIndex = 3;
            clearButton.Text = "Xóa Log";
            clearButton.UseVisualStyleBackColor = true;
            clearButton.Click += clearButton_Click;
            // 
            // updateButton
            // 
            updateButton.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            updateButton.Location = new Point(965, 99);
            updateButton.Margin = new Padding(3, 4, 3, 4);
            updateButton.Name = "updateButton";
            updateButton.Size = new Size(268, 53);
            updateButton.TabIndex = 10;
            updateButton.Text = "Cập Nhật Sinh Viên";
            updateButton.UseVisualStyleBackColor = true;
            updateButton.Click += updateButton_Click;
            // 
            // serialOutput
            // 
            serialOutput.Location = new Point(26, 181);
            serialOutput.Margin = new Padding(3, 4, 3, 4);
            serialOutput.Multiline = true;
            serialOutput.Name = "serialOutput";
            serialOutput.ReadOnly = true;
            serialOutput.ScrollBars = ScrollBars.Vertical;
            serialOutput.Size = new Size(579, 569);
            serialOutput.TabIndex = 4;
            // 
            // dataStudent
            // 
            dataStudent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataStudent.Location = new Point(638, 181);
            dataStudent.Margin = new Padding(3, 4, 3, 4);
            dataStudent.Name = "dataStudent";
            dataStudent.RowHeadersWidth = 51;
            dataStudent.RowTemplate.Height = 25;
            dataStudent.Size = new Size(579, 571);
            dataStudent.TabIndex = 5;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            label3.Location = new Point(34, 131);
            label3.Name = "label3";
            label3.Size = new Size(185, 37);
            label3.TabIndex = 6;
            label3.Text = "Serial Monitor";
            // 
            // textBoxName
            // 
            textBoxName.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            textBoxName.Location = new Point(414, 35);
            textBoxName.Margin = new Padding(3, 4, 3, 4);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(525, 34);
            textBoxName.TabIndex = 7;
            textBoxName.Text = "Nhập tên sinh viên";
            // 
            // textBoxStudentID
            // 
            textBoxStudentID.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            textBoxStudentID.Location = new Point(414, 81);
            textBoxStudentID.Margin = new Padding(3, 4, 3, 4);
            textBoxStudentID.Name = "textBoxStudentID";
            textBoxStudentID.Size = new Size(525, 34);
            textBoxStudentID.TabIndex = 8;
            textBoxStudentID.Text = "Nhập mã Sinh Viên";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(638, 131);
            label1.Name = "label1";
            label1.Size = new Size(301, 37);
            label1.TabIndex = 9;
            label1.Text = "Sinh viên có trong CSDL";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1256, 849);
            Controls.Add(updateButton);
            Controls.Add(label1);
            Controls.Add(textBoxStudentID);
            Controls.Add(textBoxName);
            Controls.Add(label3);
            Controls.Add(dataStudent);
            Controls.Add(serialOutput);
            Controls.Add(clearButton);
            Controls.Add(addButton);
            Controls.Add(statusLabel);
            Controls.Add(Status);
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            Text = "Student Manager";
            ((System.ComponentModel.ISupportInitialize)dataStudent).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label Status;
        private Label statusLabel;
        private Button addButton;
        private Button clearButton;
        private Button updateButton;  // Thêm khai báo cho updateButton
        private TextBox serialOutput;
        private DataGridView dataStudent;
        private Label label3;
        private TextBox textBoxName;
        private TextBox textBoxStudentID;
        private Label label1;
    }
}
