using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace wannacry
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        System.Windows.Threading.DispatcherTimer disTimer;
        System.Windows.Threading.DispatcherTimer disTimer2;
        string cn_title1 = "我的电脑出了什么问题？";
        string cn_title2 = "有没有恢复这些文档的方法？";
        string cn_para1 = "您的一些重要文件被我加密保存了。\n照片、图片、文档、压缩包、音频、视频文件、exe文件等，几乎所有类型的文件都被加密了，因此不能正常打开。\n这和一般文件损坏有本质上的区别，您大可在网上找找恢复文件的方法，我敢保证，没有我们的解密服务，就算老天爷来了也不能恢复这些文档。\n";
        string cn_para2 = "当然有可恢复的方法。只能通过我们的解密服务才能恢复。我以人格担保，能提供安全有效的恢复服务。\n但这是收费的，也不能无限期的推迟。\n请点击<Decrypt>按钮，就可以免费恢复一些文档。请您放心，我是绝不会骗你的。\n但想要恢复全部文档，需要付款点费用。\n是否随时都可以固定金额付款，就会恢复的吗，当然不是，推迟付款时间越长对你不利。\n最好3天之内付款费用，过了三天费用就会翻倍。\n还有，一个礼拜之内未付款，将会永远恢复不了。\n对了，忘了告诉你，对半年以上没钱付款的穷人，会有活动免费恢复，能否轮到你，就要看您运气怎么样了。\n";
        string en_title1 = "What Happened to My Computer?";
        string en_title2 = "Can I Recover My Files?";
        string en_title3 = "How Do I Pay?";
        string en_para1 = "Your important files are encrypted.\nMany of your documents, photos, videos, databases and other files are no longer accessible because they have been encrypted. Maybe you are busy looking for a way to recover your files, but do not waste your time. Nobody can recover your files without our decryption service.\n";
        string en_para2 = "Sure. We guarantee that you can recover all your files safely and easily. But you have not so enough time.\nYou can decrypt some of your files for free. Try now by clicking .\nBut if you want to decrypt all your files, you need to pay.\nYou only have 3 days to submit the payment. After that the price will be doubled.\nAlso, if you don’t pay in 7 days, you won’t be able to recover your files forever.\nWe will have free events for users who are so poor that they couldn’t pay in 6 months.\n";
        string en_para3 = "Payment is accepted in Bitcoin only. For more information, click .\nPlease check the current price of Bitcoin and buy some bitcoins. For more information, click .\nAnd send the correct amount to the address specified in this window.\nAfter your payment, click . Best time to check: 9:00am – 11:00am GMT from Monday to Friday.\nOnce the payment is checked, you can start decrypting your files immediately.\nContact\nIf you need our assistance, send a message by clicking contact Us.\nWe strongly recommend you to not remove this software, and disable your anti-virus for a while, until you pay and the payment gets processed. If your anti-virus gets updated and removes this software automatically, it will not be able to recover your files even if you pay!";
        int day = 3;
        int hour = 0;
        int minute = 0;
        int second = 0;
        int day2 = 6;
        int hour2 = 0;
        int minute2 = 0;
        int second2 = 0;

        public MainWindow()
        {
            InitializeComponent();
            comboBox.Items.Add("Chinese (Simplified)");
            comboBox.Items.Add("English");
            comboBox.SelectedIndex = 0;

            disTimer = new System.Windows.Threading.DispatcherTimer();
            disTimer.Interval = new TimeSpan(0, 0, 0, 1); //参数分别为：天，小时，分，秒。此方法有重载，可根据实际情况调用。
            disTimer.Tick += new EventHandler(count_time); //每一秒执行的方法
            disTimer.Start();

            disTimer2 = new System.Windows.Threading.DispatcherTimer();
            disTimer2.Interval = new TimeSpan(0, 0, 0, 1); //参数分别为：天，小时，分，秒。此方法有重载，可根据实际情况调用。
            disTimer2.Tick += new EventHandler(count_time2); //每一秒执行的方法
            disTimer2.Start();
        }

        private void comboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            richTextBox.Document.Blocks.Clear();
            if (comboBox.SelectedIndex == 0)
                initChinese();
            else
                initEnglish();
        }

        void count_time(object sender, EventArgs e)
        {
            second--;
            if (second < 0) {
                second = 59;
                minute--;
                if (minute < 0) {
                    minute = 59;
                    hour--;
                    if (hour < 0) {
                        hour = 23;
                        day--;
                        if (day < 0) {
                            //倒计时结束
                        }
                    }
                }
            }
            string time = String.Format("{0:D2}:{1:D2}:{2:D2}:{3:D2}", day, hour, minute, second);
            label_time1.Content = time;
        }

        void count_time2(object sender, EventArgs e)
        {
            second2--;
            if (second2 < 0) {
                second2 = 59;
                minute2--;
                if (minute2 < 0) {
                    minute2 = 59;
                    hour2--;
                    if (hour2 < 0) {
                        hour2 = 23;
                        day2--;
                        if (day2 < 0) {
                            //倒计时结束
                        }
                    }
                }
            }
            string time = String.Format("{0:D2}:{1:D2}:{2:D2}:{3:D2}", day2, hour2, minute2, second2);
            label_time2.Content = time;
        }

        private void initChinese() {
            richTextBox.Document.Blocks.Clear();
            var t1 = new Paragraph();
            var tt1 = new Run(cn_title1);
            t1.SetValue(Paragraph.LineHeightProperty, 3.0);
            t1.Inlines.Add(tt1);
            t1.FontSize = 17;
            t1.FontWeight = FontWeights.Bold;
            richTextBox.Document.Blocks.Add(t1);

            var p1 = new Paragraph();
            var pp1 = new Run(cn_para1);
            p1.SetValue(Paragraph.LineHeightProperty, 3.0);
            p1.Inlines.Add(pp1);
            p1.FontSize = 13;
            p1.FontWeight = FontWeights.Normal;
            richTextBox.Document.Blocks.Add(p1);

            var t2 = new Paragraph();
            var tt2 = new Run(cn_title2);
            t2.SetValue(Paragraph.LineHeightProperty, 3.0);
            t2.Inlines.Add(tt2);
            t2.FontSize = 17;
            t2.FontWeight = FontWeights.Bold;
            richTextBox.Document.Blocks.Add(t2);

            var p2 = new Paragraph();
            var pp2 = new Run(cn_para2);
            p2.SetValue(Paragraph.LineHeightProperty, 3.0);
            p2.Inlines.Add(pp2);
            p2.FontSize = 13;
            p2.FontWeight = FontWeights.Normal;
            richTextBox.Document.Blocks.Add(p2);
        }
        private void initEnglish()
        {
            richTextBox.Document.Blocks.Clear();
            var t1 = new Paragraph();
            var tt1 = new Run(en_title1);
            t1.SetValue(Paragraph.LineHeightProperty, 3.0);
            t1.Inlines.Add(tt1);
            t1.FontSize = 17;
            t1.FontWeight = FontWeights.Bold;
            richTextBox.Document.Blocks.Add(t1);

            var p1 = new Paragraph();
            var pp1 = new Run(en_para1);
            p1.SetValue(Paragraph.LineHeightProperty, 3.0);
            p1.Inlines.Add(pp1);
            p1.FontSize = 13;
            p1.FontWeight = FontWeights.Normal;
            richTextBox.Document.Blocks.Add(p1);

            var t2 = new Paragraph();
            var tt2 = new Run(en_title2);
            t2.SetValue(Paragraph.LineHeightProperty, 3.0);
            t2.Inlines.Add(tt2);
            t2.FontSize = 17;
            t2.FontWeight = FontWeights.Bold;
            richTextBox.Document.Blocks.Add(t2);

            var p2 = new Paragraph();
            var pp2 = new Run(en_para2);
            p2.SetValue(Paragraph.LineHeightProperty, 3.0);
            p2.Inlines.Add(pp2);
            p2.FontSize = 13;
            p2.FontWeight = FontWeights.Normal;
            richTextBox.Document.Blocks.Add(p2);

            var t3 = new Paragraph();
            var tt3 = new Run(en_title3);
            t3.SetValue(Paragraph.LineHeightProperty, 3.0);
            t3.Inlines.Add(tt3);
            t3.FontSize = 17;
            t3.FontWeight = FontWeights.Bold;
            richTextBox.Document.Blocks.Add(t3);

            var p3 = new Paragraph();
            var pp3 = new Run(en_para3);
            p3.SetValue(Paragraph.LineHeightProperty, 3.0);
            p3.Inlines.Add(pp3);
            p3.FontSize = 13;
            p3.FontWeight = FontWeights.Normal;
            richTextBox.Document.Blocks.Add(p3);
        }


        private void button_check_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("不给钱就加密", "付钱", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void button_decrypt_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("给钱才能解密", "解密", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void Hyperlink_Click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(new System.Diagnostics.ProcessStartInfo(label_contact.NavigateUri.ToString()));
        }

        private void button_copy_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("代码自己写吧", "复制", MessageBoxButton.OK, MessageBoxImage.Information);
        }

    }
}
