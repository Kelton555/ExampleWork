using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using TicTacToeFinal.Models;

namespace TicTacToeFinal.Controllers
{
    public class HomeController : Controller
    {
        [HttpGet]
        public IActionResult Index()
        {
            var model = new TicTacToeModel();
            model.Board = (String) TempData.Peek("Board")! ?? model.Board; // if there is existing data, use that, otherwise use the default starting board
            model.Turn = (String) TempData.Peek("Turn")! ?? model.Turn;

            return View(model); // send the game to the view
        }

        [HttpGet]
        public IActionResult NewGame()
        {
            TempData.Remove("Board"); // remove existing data so that the next index() will return a new board
            TempData.Remove("Turn");

            return RedirectToAction("Index");
        }

        [HttpPost]
        public IActionResult MakeMove(TicTacToeModel model, int position)
        {
            model.MakeMove(position);
            TempData["Board"] = model.Board; // temp data is used so that the board can be retrieved even with regular httpgets
            TempData["Turn"] = model.Turn;
            return RedirectToAction("Index"); // redirect to a get to prevent double-posting
        }
    }
}
