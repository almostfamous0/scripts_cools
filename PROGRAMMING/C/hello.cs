// mcs hello.cs -r:System.Windows.Forms.dll -out:hello.exe
using System;
using System.Windows.Forms;

class Program
{
    [STAThread]
    static void Main()
    {
        Console.WriteLine("Hello, World!");
        MessageBox.Show("Olá, mundo!", "Mensagem Simples");
    }
}

