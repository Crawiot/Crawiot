using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace Crawiot
{
    class Program
    {
        private const string BASE = "http://crawiot.lan/api/motion";
        private static readonly StringContent StringContent = new("");
        private static readonly HttpClient Client = new();

        static async Task Main(string[] args)
        {
            await Rotate(85);
            await Move(170);
            await Task.Delay(500);
            await Stop();
            // await Rotate90(true);
            // await Stop();
            // await Move();
            // await Task.Delay(10_000);
        }

        private static Task Move(int units = 110)
        {
            return Client.PostAsync(GetMoveUrl(units), StringContent);
        }

        private static async Task Rotate90(bool isLeft)
        {
            for (var i = 0; i < 6; i++)
            {
                if (isLeft)
                    await RotateToLeft();
                else
                    await RotateToRight();
            }
        }

        private static Task Rotate(int units)
        {
            return Client.PostAsync(GetRotateUrl(units), StringContent);
        }

        private static Task Stop()
        {
            return Client.PostAsync(GetMoveUrl(90), StringContent);
        }

        private static async Task RotateToRight() {
            await Rotate(65);
            await Task.Delay(300);
            await Move(110);
            await Task.Delay(500);
            await Move(90);
            await Task.Delay(300);
            await Rotate(105);
            await Task.Delay(300);
            await Move(70);
            await Task.Delay(500);
            await Rotate(85);
            await Move(90);
            await Task.Delay(300);
        }

        private static async Task RotateToLeft() {
            await Rotate(105);
            await Task.Delay(300);
            await Move(110);
            await Task.Delay(500);
            await Move(90);
            await Task.Delay(300);
            await Rotate(65);
            await Task.Delay(300);
            await Move(70);
            await Task.Delay(500);
            await Rotate(85);
            await Move(90);
            await Task.Delay(300);
        }
        
        private static Uri GetRotateUrl(int units)
        {
            return new($"{BASE}/rotate?units={units}");
        }

        private static Uri GetMoveUrl(int units)
        {
            return new($"{BASE}/move?units={units}");
        }
    }
}