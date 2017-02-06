using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Threading;
using System.Net.Sockets;
using Mono.Data.Sqlite;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;
using System.Net.NetworkInformation;

public class Clients
{
	public Socket[] Client = new Socket[10];
	public byte NumClients;
}

// State object for reading client data asynchronously
public class TCPNetworkObject
{
	// Client  socket.
	public Socket workSocket = null;
	// Size of receive buffer.
	public const int BufferSize = 1024;
	// Receive buffer.
	public byte[] buffer = new byte[BufferSize];
	// Received data string.
	public StringBuilder sb = new StringBuilder();

	public static IPAddress ipAddress = null;
}

public class UDPNetworkObject
{
	public IPEndPoint EndPoint;
	public UdpClient Client;

}

public class AsynchronousSocketListener
{
	// Thread signal.
	public static ManualResetEvent allDone = new ManualResetEvent(false);

	public static Clients clients = new Clients();
	public static SqliteConnection m_dbConnection;
	public static int CounterDisconnect = 0;

	public AsynchronousSocketListener()
	{
	}

	public static void StartListening()
	{
		// Data buffer for incoming data.
		byte[] bytes = new Byte[1024];

		for(int i = 0; i < 4; i++)
		{
			clients.Client[i] = null;
		}

		// Establish the local endpoint for the socket.
		// The DNS name of the computer
		// running the listener is "host.contoso.com".
		TCPNetworkObject.ipAddress = IPAddress.Any;
		IPEndPoint localEndPoint = new IPEndPoint(TCPNetworkObject.ipAddress, 8080);

		// Create a TCP/IP socket.
		Socket listener = new Socket(AddressFamily.InterNetwork,
			SocketType.Stream, ProtocolType.Tcp);

		// DataBase

		if (File.Exists("MyDatabase.sqlite"))
		{
			Console.WriteLine("Using existing DataBase");

			m_dbConnection = new SqliteConnection("Data Source=MyDatabase.sqlite; Version=3;");
			m_dbConnection.Open();
		}
		else
		{
			SqliteConnection.CreateFile("MyDatabase.sqlite");

			m_dbConnection = new SqliteConnection("Data Source=MyDatabase.sqlite; Version=3;");
			m_dbConnection.Open();

			string LoginTable = "create table Login (user varchar(20), pass varchar(20))";
			SqliteCommand Command = new SqliteCommand(LoginTable, m_dbConnection);
			Command.ExecuteNonQuery();

			Console.WriteLine("Creating New DataBase");
		}

		// Bind the socket to the local endpoint and listen for incoming connections.
		try
		{
			listener.Bind(localEndPoint);
			listener.Listen(100);

			foreach (var netinterface in NetworkInterface.GetAllNetworkInterfaces())
			{
				if(netinterface.NetworkInterfaceType == NetworkInterfaceType.Wireless80211 || netinterface.NetworkInterfaceType == NetworkInterfaceType.Ethernet)
				{
					foreach(var addrInfo in netinterface.GetIPProperties().UnicastAddresses)
					{
						if(addrInfo.Address.AddressFamily == AddressFamily.InterNetwork)
						{
							Console.WriteLine("Ip {0}",addrInfo.Address.ToString());
						}
					}
				}
			}


			/*string MyIp = ""; 

			var host = Dns.GetHostEntry(Dns.GetHostName());
			foreach (var ip in host.AddressList)
			{
				if (ip.AddressFamily == AddressFamily.InterNetwork)
				{
					MyIp = ip.ToString();
				}
			}*/

			while (true)
			{
				try
				{
					// Set the event to nonsignaled state.
					allDone.Reset();

					// Start an asynchronous socket to listen for connections.
					Console.WriteLine("Waiting for a connection...");

					//Console.WriteLine("\nIP {0}", MyIp);

					listener.BeginAccept(
						new AsyncCallback(AcceptCallback),
						listener);


					// Wait until a connection is made before continuing.
					allDone.WaitOne();


					while(clients.NumClients >= 4)
					{

					}
				}
				catch (SocketException)
				{
					Console.WriteLine("Client Disconnected ...");
				}
			}

		}
		catch (Exception e)
		{
			Console.WriteLine(e.ToString());
		}
		Console.WriteLine("\nPress ENTER to continue...");
		Console.Read();
	}

	public static void AcceptCallback(IAsyncResult ar)
	{
		// Signal the main thread to continue.
		allDone.Set();
		// Get the socket that handles the client request.
		Socket listener = (Socket)ar.AsyncState;
		Socket handler = listener.EndAccept(ar);
		if (clients.NumClients < 4)
		{

			// Create the state object.
			TCPNetworkObject state = new TCPNetworkObject();
			state.workSocket = handler;
			handler.BeginReceive(state.buffer, 0, TCPNetworkObject.BufferSize, 0,
				new AsyncCallback(LoginReadCallback), state);

		}else
		{
			handler.Disconnect(false);
		}
	}

	public static void LoginReadCallback(IAsyncResult ar)
	{
		String content = String.Empty;
		TCPNetworkObject state = (TCPNetworkObject)ar.AsyncState;
		Socket handler = state.workSocket;
		int bytesRead = 0;
		bool isLoginInformationCorrect = true;

		// Read data from the client socket. 
		try
		{
			bytesRead = handler.EndReceive(ar);
		}
		catch (SocketException)
		{
			Console.WriteLine("Client Disconnected ...");
		}

		if (bytesRead > 0)
		{
			// Console.WriteLine("User Connected: {0}", Encoding.ASCII.GetString(state.buffer, 8, bytesRead));
			// UserName & Password
			String loginData = Encoding.ASCII.GetString(state.buffer, 8, bytesRead);

			// UserName
			String userName = "";
			int index = loginData.IndexOf(':');
			if (index > 0)
				userName = loginData.Substring(0, index);
			//Console.WriteLine("Username: {0}", userName);

			// PassWord
			string passWord = "";
			passWord = loginData.Substring(loginData.LastIndexOf(':') + 1);
			//Console.WriteLine("Password: {0}", passWord);

			string sql = "select * from Login where user=@username and pass=@password";
			SqliteCommand userSearch = new SqliteCommand(sql, m_dbConnection);
			userSearch.Parameters.AddWithValue("@username", userName);
			userSearch.Parameters.AddWithValue("@password", passWord);

			SqliteDataReader reader = userSearch.ExecuteReader();

			if (reader.Read())
				Console.WriteLine("User Already Registered");
			else
			{
				string sqlUserName = "select * from Login where user=@patata";
				SqliteCommand searchUserName = new SqliteCommand(sqlUserName, m_dbConnection);
				searchUserName.Parameters.AddWithValue("@patata", userName);
				SqliteDataReader readerUserName = searchUserName.ExecuteReader();

				if (readerUserName.Read())
				{
					isLoginInformationCorrect = false;
				}
				else
				{
					Console.WriteLine("Registering User");

					string LoginUser = "insert into Login (user,pass) values (@username,@password)";
					SqliteCommand command = new SqliteCommand(LoginUser, m_dbConnection);
					command.Parameters.AddWithValue("@username", userName);
					command.Parameters.AddWithValue("@password", passWord);
					command.ExecuteNonQuery();
				}
			}

			if (isLoginInformationCorrect)
			{
				state = new TCPNetworkObject();
				state.workSocket = handler;
				handler.BeginReceive(state.buffer, 0, TCPNetworkObject.BufferSize, 0,
					new AsyncCallback(ReadCallback), state);

				// Adding clients
				byte i = 0;

				while (i < 4 && clients.Client[i] != null)
				{
					i++;
				}

				clients.Client[i] = handler;
				byte[] PlayerIndex = new byte[8];

				// SFML need Size in the message
				PlayerIndex[3] = 4;
				// Index of the Player
				PlayerIndex[7] = i;
				clients.NumClients++;

				// Control of the number of players
				while (clients.NumClients < 4)
				{

				}
				handler.BeginSend(PlayerIndex, 0, sizeof(int) * 2, 0,
					new AsyncCallback(SendCallback), handler);
			}
			else
			{
				state = new TCPNetworkObject();
				state.workSocket = handler;
				handler.BeginReceive(state.buffer, 0, TCPNetworkObject.BufferSize, 0,
					new AsyncCallback(LoginReadCallback), state);

				byte[] PlayerIndex = new byte[8];

				// SFML need Size in the message
				PlayerIndex[3] = 4;
				// Index of the Player
				PlayerIndex[7] = 255;

				handler.BeginSend(PlayerIndex, 0, sizeof(int) * 2, 0,
					new AsyncCallback(SendCallback), handler);

			}
		}
	}

	public static void ReadCallback(IAsyncResult ar)
	{
		String content = String.Empty;

		// Retrieve the state object and the handler socket
		// from the asynchronous state object.
		TCPNetworkObject state = (TCPNetworkObject)ar.AsyncState;
		Socket handler = state.workSocket;
		int bytesRead = 0;

		// Read data from the client socket. 
		try
		{
			bytesRead = handler.EndReceive(ar);
		}
		catch (SocketException)
		{
			for (int i = 0; i < clients.NumClients; i++)
			{
				if (clients.Client[i] == handler)
				{
					Disconnect(i);
				}
			}
			Console.WriteLine("Client Disconnected ...");
		}


		if (bytesRead > 0)
		{
			if (bytesRead > 8)
			{
				// There  might be more data, so store the data received so far.
				/*state.sb.Append(Encoding.ASCII.GetString(
            state.buffer, 0, bytesRead));*/

				// Check for end-of-file tag. If it is not there, read 
				// more data.
				//content = state.sb.ToString();
				//if (content.IndexOf("\0") > -1)
				//{
				// All the data has been read from the 
				// client. Display it on the console.
				Console.WriteLine("Read {0} bytes from socket. \n Data : {1}",
					bytesRead, (float)System.BitConverter.ToSingle(state.buffer, 0));

				// Echo the data back to the client.
				Send(handler, state.buffer, bytesRead);

				state = new TCPNetworkObject();
				state.workSocket = handler;
				try
				{
					handler.BeginReceive(state.buffer, 0, TCPNetworkObject.BufferSize, 0,
						new AsyncCallback(ReadCallback), state);
				}
				catch (SocketException)
				{
					for (int i = 0; i < clients.NumClients; i++)
					{
						if (clients.Client[i] == handler)
						{
							Disconnect(i);
						}
					}
					Console.WriteLine("Client Disconnected ...");
				}

				//}
				/*else
        {
            // Not all data received. Get more.
            handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
            new AsyncCallback(ReadCallback), state);
        }*/
			}
			else
			{
				for (int i = 0; i < clients.NumClients; i++)
				{
					if (clients.Client[i] == handler)
					{
						Disconnect(i);
						CounterDisconnect += 1;
					}
				}
				if (CounterDisconnect >= 2) {
					Environment.Exit (1);
				}
				Console.WriteLine("Client Disconnected ...");
			}
		}

	}

	private static void Send(Socket handler, byte[] data, int size)
	{
		// Convert the string data to byte data using ASCII encoding.
		//byte[] byteData = Encoding.ASCII.GetBytes(data);


		// Begin sending the data to the remote device.
		for (int i = 0; i < clients.NumClients; i++)
		{
			try
			{
				if(clients.Client[i] != null)
				{
					clients.Client[i].BeginSend(data, 0, size, 0,
						new AsyncCallback(SendCallback), clients.Client[i]);
				}
			}
			catch (SocketException)
			{
				Disconnect(i);
				Console.WriteLine("Client Disconnected ...");
			}
		}
	}

	private static void SendCallback(IAsyncResult ar)
	{
		// Retrieve the socket from the state object.s
		Socket handler = (Socket)ar.AsyncState;
		try
		{

			// Complete sending the data to the remote device.
			int bytesSent = handler.EndSend(ar);
			Console.WriteLine("Sent {0} bytes to client.", bytesSent);

			/* handler.Shutdown(SocketShutdown.Both);
       handler.Close();*/

		}
		catch (SocketException)
		{
			for (int i = 0; i < clients.NumClients; i++)
			{
				if (clients.Client[i] == handler)
				{
					Disconnect(i);
				}
			}

		}
	}

	private static void Disconnect(int index)
	{
		clients.Client[index] = null;
		clients.NumClients--;
	}

	public static int Main(String[] args)
	{
		Console.WriteLine("Starting...");
		Thread.Sleep(1000);
		Thread UDPThread = new Thread(new ThreadStart(UDPSocketListener.StartToListen));
		UDPThread.Start();
		StartListening();
		return 0;
	}
}

public class UDPSocketListener
{
	public UDPSocketListener() { }

	public static bool messageReceived = false;
	public static bool messageSent = false;
	public static EndPoint[] UDPClients = new EndPoint[10];
	public static int NumClients = 0;

	public static void StartToListen()
	{

		// Receive a message and write it to the console. 
		IPEndPoint EndPoint = new IPEndPoint(IPAddress.Any, 8080);

		UdpClient Client = new UdpClient(EndPoint);
		UDPNetworkObject Net = new UDPNetworkObject();
		Net.EndPoint = EndPoint;
		Net.Client = Client;
		// Do some work while we wait for a message. 
		while (true)
		{
			messageReceived = false;
			//Console.WriteLine("listening for messages");

			Client.BeginReceive(new AsyncCallback(ReceiveCallback), Net);

			while (!messageReceived)
			{
				// Do something 
			}

		}
		//Net.Client.Close();
	}

	public static void ReceiveCallback(IAsyncResult ar)
	{
		UdpClient Client = (UdpClient)((UDPNetworkObject)(ar.AsyncState)).Client;
		IPEndPoint EndPoint = (IPEndPoint)((UDPNetworkObject)(ar.AsyncState)).EndPoint;
		Byte[] Bytes = Client.EndReceive(ar, ref EndPoint);
		messageReceived = true;

		bool save = true;
		bool valid = false;

		for (int i = 0; i < NumClients; i++)
		{
			if (UDPClients[i] != null)
			{
				if (UDPClients[i].Equals(EndPoint))
				{
					save = false;
					valid = true;
				}
				else
				{

				}
			}
		}

		if (save && NumClients < 4)
		{
			UDPClients[NumClients] = EndPoint;
			Console.WriteLine("Add Clients");
			valid = true;
			NumClients++;

		}

		if (valid)
		{
			BroadCast(Bytes);
		}
	}

	static Socket Socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

	private static void BroadCast(Byte[] data)
	{
		/*Socket Socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
    IPAddress BroadCast = IPAddress.Parse("127.0.0.1");
    IPEndPoint EndPoint = new IPEndPoint(BroadCast, 8081);
    Socket.SendTo(data, EndPoint);
    IPEndPoint EndPoint2 = new IPEndPoint(BroadCast, 8082);
    Socket.SendTo(data, EndPoint2);*/



		//Console.WriteLine("{0}",data.Length);
		for (int i = 0; i < NumClients; i++)
		{
			if (UDPClients[i] != null)
				Socket.SendTo(data, UDPClients[i]);
		}
	}

	private static void Send(string server, Byte[] data)
	{
		messageSent = false;
		// create the udp socket 
		UdpClient Client = new UdpClient();
		//Client.EnableBroadcast = true;

		Client.Connect(server, 8080);
		// send the message 
		// the destination is defined by the call to .Connect ()
		Client.BeginSend(data, data.Length, new AsyncCallback(SendCallback), Client);
		// Do some work while we wait for the send to complete . For // this example, we'll just sleep
		while (!messageSent)
		{
			//Thread.Sleep(100);
		}


	}

	private static void SendCallback(IAsyncResult ar)
	{
		UdpClient client = (UdpClient)ar.AsyncState;
		Console.WriteLine("number of bytes sent: {0}", client.EndSend(ar));
		messageSent = true;
	}


}