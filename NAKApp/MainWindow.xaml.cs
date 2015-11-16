using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace NAKApp
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private AxNAKCoreLib.AxNAKCore _view3d = null;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _view3d = new AxNAKCoreLib.AxNAKCore();
            _hostMain.Child = _view3d;

            _sliderRed.Value = (short)(_view3d.EffectRed);
            _sliderGreen.Value = (short)(_view3d.EffectGreen);
            _sliderBlue.Value = (short)(_view3d.EffectBlue);

//            _view3d.EffectInvert = false;
            
            _sliderGamma.Value = (short)_view3d.EffectGamma;
            _sliderContrast.Value = (short)_view3d.EffectContrast;
            _sliderBrightness.Value = (short)_view3d.EffectBrightness;
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            //대화상자를 통해서 obj 파일을 읽어옴
            OpenFileDialog fileDialog = new System.Windows.Forms.OpenFileDialog();
            fileDialog.Filter = "Obj Files|*.obj";
            fileDialog.Title = "Obj 파일을 선택하세요.";
            DialogResult result = fileDialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                string fname = fileDialog.FileName;
                _view3d.OpenObject(fname);

                BitmapImage bitmap = new BitmapImage();
                bitmap.BeginInit();
                bitmap.UriSource = new Uri(_view3d.UVImage.ToString());
                bitmap.EndInit();
                _UVImage.Source = bitmap;
                //_view3d.OpenObject("C:\\Projects\\NAKProject\\NAK\\Support\\data\\cube.obj");
            }
        }

        private void _sliderRed_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            _view3d.EffectRed = (short)(_sliderRed.Value);
        }

        private void _sliderGreen_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            _view3d.EffectGreen = (short)(_sliderGreen.Value);
        }

        private void _sliderBlue_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            _view3d.EffectBlue = (short)(_sliderBlue.Value);
        }

        private void _UVImage_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void _chkInvert_Checked(object sender, RoutedEventArgs e)
        {
            _view3d.EffectInvert = true;
        }
        
        private void _chkInvert_Unchecked(object sender, RoutedEventArgs e)
        {
            _view3d.EffectInvert = false;
        }

        private void _sliderGamma_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            _view3d.EffectGamma = (short)(_sliderGamma.Value);
        }

        private void _sliderContrast_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            _view3d.EffectContrast = (short)(_sliderContrast.Value);
        }

        private void _sliderBrightness_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            _view3d.EffectBrightness = (short)(_sliderBrightness.Value);
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            if (_UVImage.Source == null)
            {
                System.Windows.Forms.MessageBox.Show("열려진 Obj파일이 없습니다.\n열기 버튼을 클릭해서 Obj 파일을 여십시오.");
                return;
            }

            //대화상자를 통해서 obj 파일을 읽어옴
            SaveFileDialog fileDialog = new System.Windows.Forms.SaveFileDialog();
            fileDialog.Filter = "Json Files|*.json";
            fileDialog.Title = "저장할 Data 파일을 지정하세요.";
            DialogResult result = fileDialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                string fname = fileDialog.FileName;
                _view3d.SaveObject(fname);
            }
        }

        private void _btnSubdiv_Click(object sender, RoutedEventArgs e)
        {
            _view3d.SubdivisionLoop();
        }
    }
}
