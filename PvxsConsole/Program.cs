
using PvxsCLR;

// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

const string PV_NAME = "TEST:MODEL_RBV";

PvxsCLR.ContextWrapper context=new();

context.Initialise();
var d= context.Get(PV_NAME);

Console.WriteLine("Bye!");