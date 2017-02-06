#ifndef __NETWORKMANAGER_H__
#define __NETWORKMANAGER_H__

#include <SFML/Network.hpp>
/**
 * Enum
 * Which type of information is going to send udp
 */
enum TypeInformation
{
	kTypeInformation_Player,
	kTypeInformation_SpikeBox,
	kTypeInformation_Victory,
};
/**
 * Struct
 * All the information that the player needs to receive and send
 */
struct PlayerInfo {
	float PosX;
	float PosY;
	float Rotation;
	int Points;
};
/**
 * Struct
 * All the information that the coin needs to receive and send
 */
struct CoinInfo {
	float PosX;
	float PosY;
	float Rotation;
};

/**
 * Struct
 * All the information that the spike box needs to receive and send
 */
struct SpikeBoxInfo {
	float PosX;
	float PosY;
	float Rotation;
};

class NetWorkManager
{
public:
    /// Destructor
	~NetWorkManager() {};
	/// Get Instance
	static NetWorkManager* GetInstance();
	/**
	* Connect to the game.
	* @param insertedIP IP.
	* @param username Username.
	* @param password Password.
	* @return The path.
	*/
	bool Connect(const char* insertedIP, const char* username, const char* password);
	/// Send Game information (TCP).
	void SendGameInfoTCP(CoinInfo* info);
	/// Send Player information (UDP).
	void SendPlayerInfoUDP(PlayerInfo* info);
	/// Send SpikeBox information (UDP).
	void SendSpikeBoxInfoUDP(SpikeBoxInfo* info);
	/// Send if someone wins (UDP).
	void SendVictoryUDP();
	/// Receive game information (TCP).
	bool ReceiveGameInfoTCP();
	/// Receive information (UDP)
	void ReceiveGameInfoUDP();
	/// Disconnect
	void Disconnect();
	/// Struct declaration that contains all the information that the players need.
	PlayerInfo Players[4];
	/// Struct declaration that contains all the information that the coins need.
	CoinInfo Coin;
	/// Struct declaration that contains all the information that the SpikeBox need.
	SpikeBoxInfo SpikeBox;
	/// Struct declaration that contains what type of information it is going to be.
	TypeInformation Information;
	/// Player Index
	int PlayerIndex = 0;
	/// Get points
	int GetPoints();
	/// Set points
	void SetPoints(int points);
	/// Add points
	void AddPoints(int points);
	/// Subtact points
	void SubtractPoints(int points);

private:
    /// Constructor
	NetWorkManager() {};
	/// Instance
	static NetWorkManager* Instance;
	/// TCP Socket
	sf::TcpSocket TCPSocket;
	/// UDP Socket
	sf::UdpSocket UDPSocket;
	/// IP
	const char* IP;
	/// Points
	int Points = 0;
	/// Username name
	std::string name;
};


#endif //__NETWORKMANAGER_H__
