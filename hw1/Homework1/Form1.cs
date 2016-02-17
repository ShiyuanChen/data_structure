using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Data.OleDb;
using System.Collections;
using System.Threading;

namespace Homework1
{
    public partial class Form1 : Form
    {
        static int x = 0;
        static int length = 350;
        static int front = 0;
        static int rear = 0;
        static int sta = 0;
        static int end = 2000;
        static int ptr = 0;
        static bool flag = true;
        bool init = false;
        int rate = 250;
        static int countnum = -2;
        static int judge = 0;
        static float cflag = 1;
        static string trans = "";
        DateTime tcurrent;

        static string s;
        static string strConn;
        static OleDbConnection conn;

        static string strExcel1 = "select * from [sheet1$]";
        static DataTable table1 = new DataTable();
        static OleDbDataAdapter myCommand1;

        Rectangle rect = new Rectangle();
        Rectangle backrec = new Rectangle();

        System.Windows.Forms.PaintEventArgs ep1;
        System.Windows.Forms.PaintEventArgs ep2;
        BufferedGraphicsContext current;
        BufferedGraphicsContext background;
        BufferedGraphics bg1;
        BufferedGraphics bg2;
        Graphics g1;
        Graphics g2;
        Pen p1 = new Pen(System.Drawing.Color.Blue, 2);
        Pen p2 = new Pen(System.Drawing.Color.SpringGreen, 2);
        Pen p3 = new Pen(System.Drawing.Color.Orange, 2);
        Pen p0 = new Pen(System.Drawing.Color.DarkGray, 1);

        public struct Node
        {
            public string date;
            public double force;
            public double pos;
            public double pow;
            public Node(string Date, double FORCE, double POS, double POW)
            {
                this.date = Date;
                this.force = FORCE;
                this.pos = POS;
                this.pow = POW;
            }
        };
        static Node node = new Node("", 0, 0, 0);
        static Node initnode = new Node("", 0, 0, 0);
        static List<Node> array = new List<Node>(length);

        static List<PointF> point1 = new List<PointF>(length);
        static List<PointF> point2 = new List<PointF>(length);
        static List<PointF> point3 = new List<PointF>(length);
        PointF pointl;
        PointF pointr;
        PointF pointt;
        PointF pointb;

        public static int insertQ(List<Node> array, ref int front, ref int rear, ref Node node, int n)
        {
            if ((rear + 1) % n == front)
                return 0;
            array[rear] = node;
            rear = (rear + 1) % n;
            return 1;
        }
        public static int popupQ(List<Node> array, ref int front, ref int rear, int n)
        {
            if (front == rear)
                return 0;
            array[front] = initnode;
            front = (front + 1) % n;
            return 1;
        }
        public void process()
        {
            tcurrent = DateTime.Now;
            while (x <= (end - sta) && flag)
            {

                g1.Clear(System.Drawing.Color.White);
                int nptr = 0;
                int count = 0;
                ptr = (rear - 1 + length) % length;
                node.date = Convert.ToString(table1.Rows[x + sta][0]);
                node.force = double.Parse(Convert.ToString(table1.Rows[x + sta][1]));
                node.pos = double.Parse(Convert.ToString(table1.Rows[x + sta][2]));
                trans = (Convert.ToString(table1.Rows[x + sta][4]));
                if (trans == "")
                    trans = "0";
                node.pow = double.Parse(trans);
                if ((rear + 1) % length == front)
                {
                    popupQ(array, ref front, ref rear, length);
                    insertQ(array, ref front, ref rear, ref node, length);
                }
                else
                    insertQ(array, ref front, ref rear, ref node, length);
                if (judge >= length - 1)
                {
                    judge = length - 2;
                }
                while (count < (rear + length - front) % length)
                {
                    nptr = (front + count) % length;
                    point1[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].force / 200 * cflag));
                    point2[count] = new PointF(rect.Width -1+ (count - (rear + length - front) % length + 1 ) * rect.Width / (length - 2), (float)(-array[nptr].pos / 8 * cflag));
                    point3[count] = new PointF(rect.Width -1+ (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pow * cflag));
                    count++;
                }
                textBox1.Text = node.date.ToString();
                textBox2.Text = node.force.ToString()+ " N";
                textBox3.Text = node.pos.ToString()+ " mm";
                textBox4.Text = node.pow.ToString()+ " kw" ;
                textBox5.Text = (1000f / rate).ToString("N1") + "组 /s";
                g1.DrawLine(p0, pointl, pointr);
                g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
                g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
                g1.DrawLine(p0, pointt, pointb);
                g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
                g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
                g1.DrawLines(p1, point1.ToArray());
                g1.DrawLines(p2, point2.ToArray());
                g1.DrawLines(p3, point3.ToArray());
                g1.DrawLine(p1, 5, -160, 18, -160);
                g1.DrawLine(p2, 82, -160, 95, -160);
                g1.DrawLine(p3, 170, -160, 183, -160);


                while (tcurrent.AddMilliseconds(rate) > DateTime.Now)
                {
                    Application.DoEvents();
                }
                tcurrent = DateTime.Now;
                bg1.Render();
                x++;
                judge++;
            }
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            if (!init)
            {
                bg1 = current.Allocate(ep1.Graphics, ep1.ClipRectangle);
                bg2 = background.Allocate(ep2.Graphics, ep2.ClipRectangle);
                g1 = bg1.Graphics;
                g2 = bg2.Graphics;
                g1.TranslateTransform(rect.X, (float)(rect.Y + 0.5 * rect.Height));//更改绘图原点
                g2.TranslateTransform(backrec.X, backrec.Y);//更改绘图原点
                g1.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g1.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighSpeed;
                g2.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
                g2.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighSpeed;
                g1.Clear(System.Drawing.Color.White);
                g1.DrawLine(p0, pointl, pointr);
                g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
                g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
                g1.DrawLine(p0, pointt, pointb);
                g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
                g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
                g1.DrawLine(p1, 5, -160, 18, -160);
                g1.DrawLine(p2, 82, -160, 95, -160);
                g1.DrawLine(p3, 170, -160, 183, -160);
                g2.Clear(System.Drawing.Color.LightSkyBlue);
            }
            else if (init)
            {
                g1.DrawLine(p0, pointl, pointr);
                g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
                g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
                g1.DrawLine(p0, pointt, pointb);
                g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
                g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
                g1.DrawLines(p1, point1.ToArray());
                g1.DrawLines(p2, point2.ToArray());
                g1.DrawLines(p3, point3.ToArray());
                g1.DrawLine(p1, 5, -160, 18, -160);
                g1.DrawLine(p2, 82, -160, 95, -160);
                g1.DrawLine(p3, 170, -160, 183, -160);
            }

            bg2.Render();
            bg1.Render();
        }
        public Form1()
        {
            InitializeComponent();
            this.Height = 583;
            this.Width = 945;
            this.Text = "西臂磨削数据";
            //开启双缓冲
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true); // 禁止擦除背景.
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.UpdateStyles();

            this.button1.Enabled = false;
            this.button5.Enabled = false;
            this.hScrollBar1.Enabled = false;
            this.vScrollBar1.Enabled = false;
            rect.X = 52;
            rect.Y = 30;
            rect.Height = 340;
            rect.Width = 840;
            backrec.X = 17;
            backrec.Y = 28;
            backrec.Height = 360;
            backrec.Width = 895;
            ep1 = new PaintEventArgs(this.CreateGraphics(), rect);
            ep2 = new PaintEventArgs(this.CreateGraphics(), backrec);
            current = BufferedGraphicsManager.Current;
            background = BufferedGraphicsManager.Current;
            pointl = new PointF(0, 0);
            pointr = new PointF(rect.Width + 1, 0);
            pointb = new PointF(0.5f * rect.Width, 0.5f * rect.Height);
            pointt = new PointF(0.5f * rect.Width, -0.5f * rect.Height);
            for (int i = 0; i < length; i++)
            {
                point1.Add(pointr);
                point2.Add(pointr);
                point3.Add(pointr);
            }
            label19.Text = "0.00";
            label19.Location = new Point((int)(rect.X - 29), (int)(rect.Y + 0.5 * rect.Height - 6));
            label9.Text = "0.50";
            label9.Location = new Point((int)(rect.X - 29), (int)(rect.Y + 0.25 * rect.Height - 6));
            label10.Text = "1.00";
            label10.Location = new Point((int)(rect.X - 29), (int)rect.Y);
            label11.Text = "-0.50";
            label11.Location = new Point((int)(rect.X - 35), (int)(rect.Y + 0.75 * rect.Height - 6));
            label12.Text = "-1.00";
            label12.Location = new Point((int)(rect.X - 35), (int)(rect.Y + rect.Height - 12));
            label19.BackColor = System.Drawing.Color.LightSkyBlue;
            label9.BackColor = System.Drawing.Color.LightSkyBlue;
            label10.BackColor = System.Drawing.Color.LightSkyBlue;
            label11.BackColor = System.Drawing.Color.LightSkyBlue;
            label12.BackColor = System.Drawing.Color.LightSkyBlue;
            label14.Text = "0s";
            label14.Location = new Point((int)(rect.X + rect.Width - 15), (int)(rect.Y + rect.Height) + 2);
            label15.Text = (-0.25 * length).ToString() + "s";
            label15.Location = new Point((int)(rect.X + 0.75 * rect.Width - 0.5 * label15.Width), (int)(rect.Y + rect.Height) + 2);
            label16.Text = (-0.5 * length).ToString() + "s";
            label16.Location = new Point((int)(rect.X + 0.5 * rect.Width - 0.5 * label16.Width), (int)(rect.Y + rect.Height) + 2);
            label17.Text = (-0.75 * length).ToString() + "s";
            label17.Location = new Point((int)(rect.X + 0.25 * rect.Width - 0.5 * label17.Width), (int)(rect.Y + rect.Height) + 2);
            label18.Text = (-length).ToString() + "s";
            label18.Location = new Point((int)(rect.X), (int)(rect.Y + rect.Height) + 2);
            label14.BackColor = System.Drawing.Color.LightSkyBlue;
            label15.BackColor = System.Drawing.Color.LightSkyBlue;
            label16.BackColor = System.Drawing.Color.LightSkyBlue;
            label17.BackColor = System.Drawing.Color.LightSkyBlue;
            label18.BackColor = System.Drawing.Color.LightSkyBlue;
            label13.BackColor = System.Drawing.Color.LightSkyBlue;
            label13.Text = "";
            label13.AutoSize = false;
            label13.Location = label18.Location;
            label13.Width = rect.Width;
            label13.Height = 16;
            label8.BackColor = System.Drawing.Color.LightSkyBlue;
            label8.Text = "";
            label8.AutoSize = false;
            label8.Location = label10.Location;
            label8.Width = 25;
            label8.Height = rect.Height;
            label20.Text = "西臂磨削过程曲线";
            label20.Location = new Point((int)(0.5 * this.Width - 0.5 * label20.Width), 5);
            label20.BackColor = Color.Transparent;
            hScrollBar1.Maximum = 84;
            hScrollBar1.Minimum = 42;
            vScrollBar1.Maximum = 10;
            vScrollBar1.Minimum = -10;
            this.label13.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.label13_MouseWheel);
            this.label13.MouseEnter += new System.EventHandler(this.label13_MouseEnter);
            this.label13.MouseLeave += new System.EventHandler(this.label13_MouseLeave);
            this.label8.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.label8_MouseWheel);
            this.label8.MouseEnter += new System.EventHandler(this.label8_MouseEnter);
            this.label8.MouseLeave += new System.EventHandler(this.label8_MouseLeave);
            this.hScrollBar1.Scroll += new ScrollEventHandler(this.hScrollBar1_Scroll);
            this.vScrollBar1.Scroll += new ScrollEventHandler(this.vScrollBar1_Scroll);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "暂停")
            {
                button1.Text = "继续";
                flag = false;
            }
            else if (button1.Text == "继续")
            {
                button1.Text = "暂停";
                flag = true;
                process();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openfile = new OpenFileDialog();
            openfile.Filter = "工作薄(*.xls)|*.xls|所有文件(*.*)|*.*";
            if (openfile.FilterIndex == 1 && openfile.ShowDialog() == DialogResult.OK)
            {
                s = openfile.FileName;
                strConn = "Provider=Microsoft.ACE.OLEDB.12.0;" + "Data Source=" + s + ";" + "Extended Properties=Excel 12.0 ;";
                Form2 form2 = new Form2();
                form2.Owner = this;
                form2.substrconn = strConn;
                form2.ShowDialog();

                if (form2.confirm())
                {
                    sta = form2.StartIndex();
                    end = form2.EndIndex();
                    label5.Text = "数据文件： " + s;
                    label6.Text = "起始时间： " + form2.StartTime();
                    label7.Text = "终止时间： " + form2.EndTime();
                    form2.Dispose();
                    if (init == true && conn.State == ConnectionState.Open)
                    {
                        conn.Close();
                        conn.ConnectionString = strConn;
                        conn.Open();
                        myCommand1.Dispose();
                        table1.Dispose();
                        table1 = new DataTable();
                        myCommand1 = new OleDbDataAdapter(strExcel1, strConn);
                        myCommand1.Fill(table1);
                    }
                    else
                    {
                        init = true;
                        conn = new OleDbConnection(strConn);
                        conn.Open();
                        myCommand1 = new OleDbDataAdapter(strExcel1, strConn);
                        myCommand1.Fill(table1);

                    }

                    point1.Clear();
                    point2.Clear();
                    point3.Clear();
                    for (int i = 0; i < length; i++)
                    {
                        point1.Add(pointr);
                        point2.Add(pointr);
                        point3.Add(pointr);
                    }

                    x = 0;
                    front = 0;
                    rear = 0;
                    flag = true;
                    judge = 0;
                    hScrollBar1.Value = 126 - length / 5;
                    vScrollBar1.Value = 0;
                    this.button1.Text = "暂停";
                    if (button1.Enabled == false)
                        this.button1.Enabled = true;
                    array.Clear();
                    for (int i = 0; i < length; i++)
                    {
                        array.Add(initnode);
                    }
                    this.button5.Enabled = this.button1.Enabled;
                    this.hScrollBar1.Enabled = this.button1.Enabled;
                    this.vScrollBar1.Enabled = this.button1.Enabled;
                    process();
                }
            }
        }
        private void Form1_FormClosing(object sender, FormClosedEventArgs e)
        {
            g1.Dispose();
            bg1.Dispose();
            ep1.Dispose();
            ep2.Dispose();
            conn.Close();
            this.Dispose();
            System.Diagnostics.Process.GetCurrentProcess().Kill();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (rate > 125)
            {
                countnum--;
                rate = (int)(1000 * Math.Pow(2, countnum));
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (rate < 1000)
            {
                countnum++;
                rate = (int)(1000 * Math.Pow(2, countnum));
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.Owner = this;
            form2.substrconn = strConn;
            form2.ShowDialog();
            if (form2.confirm())
            {
                sta = form2.StartIndex();
                end = form2.EndIndex();
                label6.Text = "起始时间： " + form2.StartTime();
                label7.Text = "终止时间： " + form2.EndTime();
                form2.Dispose();

                x = 0;
                front = 0;
                rear = 0;
                flag = true;
                judge = 0;
                point1.Clear();
                point2.Clear();
                point3.Clear();
                for (int i = 0; i < length; i++)
                {
                    point1.Add(pointr);
                    point2.Add(pointr);
                    point3.Add(pointr);
                }
                this.button1.Text = "暂停";
                if (button1.Enabled == false)
                    this.button1.Enabled = true;
                for (int i = 0; i < length; i++)
                    array[i] = initnode;
                process();
            }
        }
        private void label13_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0 && length > 210) //放大程序280
            {
                if (x == judge)
                {
                    if ((rear + length - front) % length < length - 5)
                    {
                        array.RemoveRange(rear, 5);
                        point1.RemoveRange(length - 5, 5);
                        point2.RemoveRange(length - 5, 5);
                        point3.RemoveRange(length - 5, 5);
                        length = length - 5;
                    }
                    else
                    {
                    }
                }
                else
                {
                    if ((rear + 1) % length == front)
                    {
                        if (front + 5 < length && rear != length - 1)
                        {
                            array.RemoveRange(front, 5);
                            point1.RemoveRange(length - 5, 5);
                            point2.RemoveRange(length - 5, 5);
                            point3.RemoveRange(length - 5, 5);
                        }
                        else if (rear == length - 1)
                        {
                            array.RemoveRange(front, 5);
                            rear -= 5;
                            point1.RemoveRange(length - 5, 5);
                            point2.RemoveRange(length - 5, 5);
                            point3.RemoveRange(length - 5, 5);
                        }
                        else if (front + 5 >= length)
                        {
                            int temp1 = length - front;
                            array.RemoveRange(front, temp1);
                            array.RemoveRange(0, 5 - temp1);
                            front = 0;
                            rear -= 5 - temp1;
                            point1.RemoveRange(length - 5, 5);
                            point2.RemoveRange(length - 5, 5);
                            point3.RemoveRange(length - 5, 5);
                        }
                        length = length - 5;
                    }
                    else if ((rear + length - front) % length < length - 5)
                    {
                        if (rear + 5 < length && front > rear)
                        {
                            array.RemoveRange(rear + 1, 5);
                            front -= 5;
                        }
                        else if (rear + 5 < length && front < rear)
                        {
                            array.RemoveRange(rear + 1, 5);
                        }
                        else if (rear + 5 >= length)
                        {
                            int temp2 = length - 1 - rear;
                            array.RemoveRange(rear + 1, temp2);
                            array.RemoveRange(0, 5 - temp2);
                            front -= 5 - temp2;
                            rear -= 5 - temp2;
                        }
                        point1.RemoveRange(length - 5, 5);
                        point2.RemoveRange(length - 5, 5);
                        point3.RemoveRange(length - 5, 5);
                        length = length - 5;
                    }
                    
                }
                point1.Clear();
                point2.Clear();
                point3.Clear();
                for (int i = 0; i < length; i++)
                {
                    point1.Add(pointr);
                    point2.Add(pointr);
                    point3.Add(pointr);
                }
            }
            else if (e.Delta < 0 && length < 420) // 缩放程序
            {
                if (judge == x)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        array.Insert(rear, initnode);
                        point1.Add(pointr);
                        point2.Add(pointr);
                        point3.Add(pointr);
                    }
                }
                else
                {
                    for (int j = 0; j < 5; j++)
                    {
                        array.Insert(rear, initnode);
                        point1.Add(pointr);
                        point2.Add(pointr);
                        point3.Add(pointr);
                    }
                    if(rear != length - 1)
                    {
                        front += 5;
                    }     
                }
                length = length + 5;
            }
            label15.Text = (-0.25 * length).ToString() + "s";
            label16.Text = (-0.5 * length).ToString() + "s";
            label17.Text = (-0.75 * length).ToString() + "s";
            label18.Text = (-length).ToString() + "s";


            g1.Clear(System.Drawing.Color.White);
            int nptr = 0;
            int count = 0;
            if (judge >= length - 1)
                judge = length - 2;
            while (count < (rear + length - front) % length)
            {
                nptr = (front + count) % length;
                point1[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].force / 200 * cflag));
                point2[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pos / 8 * cflag));
                point3[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pow * cflag));
                count++;
            }
            g1.DrawLine(p0, pointl, pointr);
            g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
            g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
            g1.DrawLine(p0, pointt, pointb);
            g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
            g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
            g1.DrawLines(p1, point1.ToArray());
            g1.DrawLines(p2, point2.ToArray());
            g1.DrawLines(p3, point3.ToArray());
            g1.DrawLine(p1, 5, -160, 18, -160);
            g1.DrawLine(p2, 82, -160, 95, -160);
            g1.DrawLine(p3, 170, -160, 183, -160);
            hScrollBar1.Value = 126 - length / 5;
            bg1.Render();
        }
        private void label13_MouseEnter(object sender, EventArgs e)
        {

            this.label13.Focus();

        }
        private void label13_MouseLeave(object sender, EventArgs e)
        {
            this.button1.Focus();
        }
        private void label8_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0 && cflag < 2)
                cflag += 0.1f;
            else if (e.Delta < 0 && cflag > 0.5)
                cflag -= 0.05f;
            if(cflag >= 1)
                vScrollBar1.Value = (int)((1 - cflag) * 10);
            else
                vScrollBar1.Value = (int)((1 - cflag) * 20);
            label9.Text = (0.5 * cflag).ToString("N2");
            label10.Text = (cflag).ToString("N2");
            label11.Text = (-0.5 * cflag).ToString("N2");
            label12.Text = (-1 * cflag).ToString("N2");
            g1.Clear(System.Drawing.Color.White);
            int nptr = 0;
            int count = 0;
            if (judge >= length - 1)
                judge = length - 2;
            while (count < (rear + length - front) % length)
            {
                nptr = (front + count) % length;
                point1[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].force / 200 * cflag));
                point2[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pos / 8 * cflag));
                point3[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pow * cflag));
                count++;
            }
            g1.DrawLine(p0, pointl, pointr);
            g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
            g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
            g1.DrawLine(p0, pointt, pointb);
            g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
            g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
            g1.DrawLines(p1, point1.ToArray());
            g1.DrawLines(p2, point2.ToArray());
            g1.DrawLines(p3, point3.ToArray());
            g1.DrawLine(p1, 5, -160, 18, -160);
            g1.DrawLine(p2, 82, -160, 95, -160);
            g1.DrawLine(p3, 170, -160, 183, -160);
            bg1.Render();
        }
        private void label8_MouseEnter(object sender, EventArgs e)
        {

            this.label8.Focus();

        }
        private void label8_MouseLeave(object sender, EventArgs e)
        {
            this.button1.Focus();
        }
        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {

            tcurrent = DateTime.Now;
            if (hScrollBar1.Value > 126 - length / 5) //放大程序
            {
                int temp3 = length - 5 * (126 - hScrollBar1.Value);
                int temp4 = length - temp3;
                if (x == judge)
                {
                    if ((rear + length - front) % length < temp4)
                    {
                        array.RemoveRange(rear, temp3);
                        point1.RemoveRange(temp4, temp3);
                        point2.RemoveRange(temp4, temp3);
                        point3.RemoveRange(temp4, temp3);
                        length = temp4;
                    }
                }
                else
                {
                    if ((rear + 1) % length == front)
                    {
                        if (front + temp3 < length && rear != length - 1)
                        {
                            array.RemoveRange(front, temp3);
                            point1.RemoveRange(temp4, temp3);
                            point2.RemoveRange(temp4, temp3);
                            point3.RemoveRange(temp4, temp3);
                        }
                        else if (rear == length - 1)
                        {
                            array.RemoveRange(front, temp3);
                            rear -= temp3;
                            point1.RemoveRange(temp4, temp3);
                            point2.RemoveRange(temp4, temp3);
                            point3.RemoveRange(temp4, temp3);
                        }
                        else if (front + temp3 >= length)
                        {
                            int temp1 = length - front;
                            array.RemoveRange(front, temp1);
                            array.RemoveRange(0, temp3 - temp1);
                            front = 0;
                            rear -= temp3 - temp1;
                            point1.RemoveRange(temp4, temp3);
                            point2.RemoveRange(temp4, temp3);
                            point3.RemoveRange(temp4, temp3);
                        }
                        length = temp4;
                    }
                    else if ((rear + length - front) % length < temp4)
                    {
                        if (rear + temp3 < length && front > rear)
                        {
                            array.RemoveRange(rear + 1, temp3);
                            front -= temp3;
                        }
                        else if (rear + temp3 < length && front < rear)
                        {
                            array.RemoveRange(rear + 1, temp3);
                        }
                        else if (rear + temp3 >= length)
                        {
                            int temp2 = length - 1 - rear;
                            array.RemoveRange(rear + 1, temp2);
                            array.RemoveRange(0, temp3 - temp2);
                            front -= temp3 - temp2;
                            rear -= temp3 - temp2;
                        }
                        point1.RemoveRange(temp4, temp3);
                        point2.RemoveRange(temp4, temp3);
                        point3.RemoveRange(temp4, temp3);
                        length = temp4;
                    }
                    else if ((rear + length - front) % length < length - 1)
                    {
                        hScrollBar1.Value = 126 - length / 5;
                    }
                }
                point1.Clear();
                point2.Clear();
                point3.Clear();
                for (int i = 0; i < length; i++)
                {
                    point1.Add(pointr);
                    point2.Add(pointr);
                    point3.Add(pointr);
                }
            }
            else if (hScrollBar1.Value < 126 - length / 5) // 缩放程序
            {
                int temp4 = 5 * (126 - hScrollBar1.Value);
                if (judge == x)
                {
                    for (int j = 0; j < temp4 - length; j++)
                    {
                        array.Insert(rear, initnode);
                        point1.Add(pointr);
                        point2.Add(pointr);
                        point3.Add(pointr);
                    }
                }
                else
                {
                    for (int j = 0; j < temp4 - length; j++)
                    {
                        array.Insert(rear, initnode);
                        point1.Add(pointr);
                        point2.Add(pointr);
                        point3.Add(pointr);
                    }
                    if (rear != length - 1)
                    {
                        front += temp4 - length;
                    }
                }
                length = temp4;
            }
            label15.Text = (-0.25 * length).ToString() + "s";
            label16.Text = (-0.5 * length).ToString() + "s";
            label17.Text = (-0.75 * length).ToString() + "s";
            label18.Text = (-length).ToString() + "s";
            
            g1.Clear(System.Drawing.Color.White);
            int nptr = 0;
            int count = 0;
            if (judge >= length - 1)
                judge = length - 2;
            while (count < (rear + length - front) % length)
            {
                nptr = (front + count) % length;
                point1[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].force / 200 * cflag));
                point2[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pos / 8 * cflag));
                point3[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pow * cflag));
                count++;
            }
            g1.DrawLine(p0, pointl, pointr);
            g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
            g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
            g1.DrawLine(p0, pointt, pointb);
            g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
            g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
            g1.DrawLines(p1, point1.ToArray());
            g1.DrawLines(p2, point2.ToArray());
            g1.DrawLines(p3, point3.ToArray());
            g1.DrawLine(p1, 5, -160, 18, -160);
            g1.DrawLine(p2, 82, -160, 95, -160);
            g1.DrawLine(p3, 170, -160, 183, -160);
            hScrollBar1.Value = 126 - length / 5;
            bg1.Render();
            while (tcurrent.AddMilliseconds(10) > DateTime.Now)
            {
                Application.DoEvents();
            }
        }
        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            if (vScrollBar1.Value <= 0)
                cflag = 1 + (-vScrollBar1.Value) / 10f;
            else
                cflag = 1 - (vScrollBar1.Value) / 20f; 
            label9.Text = (0.5 * cflag).ToString("N2");
            label10.Text = (cflag).ToString("N2");
            label11.Text = (-0.5 * cflag).ToString("N2");
            label12.Text = (-1 * cflag).ToString("N2");
            g1.Clear(System.Drawing.Color.White);
            int nptr = 0;
            int count = 0;
            if (judge >= length - 1)
                judge = length - 2;
            while (count < (rear + length - front) % length)
            {
                nptr = (front + count) % length;
                point1[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].force / 200 * cflag));
                point2[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pos / 8 * cflag));
                point3[count] = new PointF(rect.Width - 1 + (count - (rear + length - front) % length + 1) * rect.Width / (length - 2), (float)(-array[nptr].pow * cflag));
                count++;
            }
            g1.DrawLine(p0, pointl, pointr);
            g1.DrawLine(p0, 0f, rect.Height * 0.25f, rect.Width, rect.Height * 0.25f);
            g1.DrawLine(p0, 0f, -rect.Height * 0.25f, rect.Width, -rect.Height * 0.25f);
            g1.DrawLine(p0, pointt, pointb);
            g1.DrawLine(p0, 0.25f * rect.Width, -rect.Height * 0.5f, 0.25f * rect.Width, rect.Height * 0.5f);
            g1.DrawLine(p0, 0.75f * rect.Width, -rect.Height * 0.5f, 0.75f * rect.Width, rect.Height * 0.5f);
            g1.DrawLines(p1, point1.ToArray());
            g1.DrawLines(p2, point2.ToArray());
            g1.DrawLines(p3, point3.ToArray());
            g1.DrawLine(p1, 5, -160, 18, -160);
            g1.DrawLine(p2, 82, -160, 95, -160);
            g1.DrawLine(p3, 170, -160, 183, -160);
            bg1.Render();
        }
    }
}
