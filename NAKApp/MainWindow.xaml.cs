using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
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
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            _view3d.OpenObject("C:\\Projects\\NAKProject\\NAK\\Support\\data\\27_mapping.obj");
            //_view3d.OpenObject("C:\\Projects\\NAKProject\\NAK\\Support\\data\\cube.obj");
        }
    }
}
