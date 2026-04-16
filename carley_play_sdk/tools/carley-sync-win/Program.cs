using System;
using System.IO;
using System.Net;

namespace CarleySync
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Carley Sync v1.0 - Servidor de PC para Carley Play");
            Console.WriteLine("Buscando consola por Bluetooth/USB...");

            // Lógica para enviar juego
            if(args.Length > 0) {
                SendGame(args[0]);
            }
        }

        static void SendGame(string filePath)
        {
            byte[] gameData = File.ReadAllBytes(filePath);
            Console.WriteLine($"Enviando {filePath} a la consola...");
            // Protocolo Carley Sync over Serial/BT
        }
    }
}
