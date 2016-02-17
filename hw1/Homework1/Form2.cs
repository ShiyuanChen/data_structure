using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.Data.OleDb;

namespace Homework1
{
    public partial class Form2 : Form
    {
        public string substrconn;
        int index = 0;
        int startIndex = 0;
        int endIndex = 0;
        bool flag = false;
        string startTime;
        string endTime;
        Label label3 = new Label();
        Label label4 = new Label();
        Label label5 = new Label();
        Label label6 = new Label();
        Label label7 = new Label();
        Label label8 = new Label();
        TextBox text1 = new TextBox();
        TextBox text2 = new TextBox();
        TextBox text3 = new TextBox();
        TextBox text4 = new TextBox();
        Button sbu1 = new Button();
        Button sbu2 = new Button();
        Button sbu3 = new Button();

        public Form2()
        {
            InitializeComponent();
            this.Text = "请输入起止时间";
            this.Size = new Size(328, 201);
            label3.Text = "请输入显示时间区间:";
            label3.Location = new Point(19, 10);
            label3.AutoSize = true;
            this.Controls.Add(label3);
            label4.Text = "日期:";
            label4.Location = new Point(13, 38);
            label4.AutoSize = true;
            this.Controls.Add(label4);
            label5.Text = "日期:";
            label5.Location = new Point(13, 90);
            label5.AutoSize = true;
            this.Controls.Add(label5);

            label6.Text = "时间:";
            label6.Location = new Point(155, 38);
            label6.AutoSize = true;
            this.Controls.Add(label6);

            label7.Text = "时间:";
            label7.Location = new Point(155, 90);
            label7.AutoSize = true;
            this.Controls.Add(label7);

            label8.Text = "至";
            label8.Location = new Point(155, 63);
            label8.AutoSize = true;
            this.Controls.Add(label8);
            text1.Location = new Point(48, 35);
            text1.Size = new Size(103, 21);
            text1.TabIndex = 0;
            this.Controls.Add(text1);
            text2.Location = new Point(48, 87);
            text2.Size = new Size(103, 21);
            text2.TabIndex = 2;
            this.Controls.Add(text2);
            text3.Location = new Point(190, 35);
            text3.Size = new Size(103, 21);
            text3.TabIndex = 1;
            this.Controls.Add(text3);
            text4.Location = new Point(190, 87);
            text4.Size = new Size(103, 21);
            text4.TabIndex = 3;
            this.Controls.Add(text4);
            sbu1.Location = new Point(126, 127);
            sbu1.Size = new Size(58, 26);
            sbu1.Text = "确定";
            sbu1.TabIndex = 4;
            this.Controls.Add(sbu1);
            sbu2.Location = new Point(208, 127);
            sbu2.Size = new Size(58, 26);
            sbu2.Text = "取消";
            sbu2.TabIndex = 5;
            this.Controls.Add(sbu2);
            sbu3.Location = new Point(44, 127);
            sbu3.Size = new Size(58, 26);
            sbu3.Text = "全部";
            sbu3.TabIndex = 5;
            this.Controls.Add(sbu3);
            this.sbu1.Click += new System.EventHandler(sbu1_Click);
            this.sbu2.Click += new System.EventHandler(sbu2_Click);
            this.sbu3.Click += new System.EventHandler(sbu3_Click);
        }
        private void sbu1_Click(object sender, EventArgs e)
        {
            string a = text1.Text.Replace(" ", "");
            string b = text3.Text.Replace(" ", "");
            string c = text2.Text.Replace(" ", "");
            string d = text4.Text.Replace(" ", "");
            OleDbConnection sconn = new OleDbConnection(substrconn);
            string strExcel2 = "select * from [sheet1$A1:A]";
            DataTable table2 = new DataTable();
            sconn.Open();
            OleDbDataAdapter myCommand2 = new OleDbDataAdapter(strExcel2, substrconn);
            myCommand2.Fill(table2);
            int temp = table2.Rows.Count;
            while (index < temp)
            {
                if (Convert.ToString(table2.Rows[index][0]) == (a + " " + b))
                {
                    startIndex = index;
                    startTime = Convert.ToString(table2.Rows[index][0]);
                    while (index < temp)
                    {
                        if (Convert.ToString(table2.Rows[index][0]) == (c + " " + d))
                        {
                            endIndex = index;
                            endTime = Convert.ToString(table2.Rows[index][0]);
                            flag = true;
                            sconn.Close();
                            sconn.Dispose();
                            table2.Dispose();
                            myCommand2.Dispose();
                            this.Close();
                        }
                        index++;
                    }
                }
                index++;
            }
            if (!flag)
            {
                MessageBox.Show(this, "未找到该区间记录，请重新输入！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Question);
                text1.Text = "";
                text2.Text = "";
                text3.Text = "";
                text4.Text = "";
                sconn.Close();
                sconn.Dispose();
                table2.Dispose();
                myCommand2.Dispose();
            }
        }
        private void sbu2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void sbu3_Click(object sender, EventArgs e)
        {
            OleDbConnection sconn = new OleDbConnection(substrconn);
            string strExcel2 = "select * from [sheet1$A1:A]";
            DataTable table2 = new DataTable();
            sconn.Open();
            OleDbDataAdapter myCommand2 = new OleDbDataAdapter(strExcel2, substrconn);
            myCommand2.Fill(table2);
            int temp = table2.Rows.Count;
            while(Convert.ToString(table2.Rows[temp - 1][0]) == "")
                temp--;
            startIndex = 0;
            endIndex = temp - 1;
            startTime = Convert.ToString(table2.Rows[0][0]);
            endTime = Convert.ToString(table2.Rows[endIndex][0]);
            flag = true;
            sconn.Close();
            sconn.Dispose();
            table2.Dispose();
            myCommand2.Dispose();
            this.Close();
        }
        public int StartIndex()
        {
            return startIndex;
        }
        public int EndIndex()
        {
            return endIndex;
        }
        public bool confirm()
        {
            return flag;
        }
        public string StartTime()
        {
            return startTime;
        }
        public string EndTime()
        {
            return endTime;
        }
    }
}
