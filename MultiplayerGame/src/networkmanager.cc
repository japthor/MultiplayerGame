#include "networkmanager.h"
#include "scene.h"
#include <iostream>

NetWorkManager* NetWorkManager::Instance = nullptr;


NetWorkManager* NetWorkManager::GetInstance()
{
    if (Instance == nullptr)
        Instance = new NetWorkManager();
    
    return Instance;
}

bool NetWorkManager::Connect(const char* insertedIP, const char* username, const char* password)
{
    sf::Packet packetReceive;
    IP = insertedIP;
    
    const unsigned short TCPPort = 8080;
    const std::string IPAddress(IP);
    printf("\nWaiting Connection...");
    
    TCPSocket.setBlocking(true);
    
    if (TCPSocket.connect(IPAddress, TCPPort) != sf::Socket::Done) {
        printf("error TCPConnect");
        return false;
    }
    
    TCPSocket.setBlocking(false);
    
    
    sf::Packet packetSend;
    
    std::hash<std::string>  hash;
    std::string pass = password;
    
    std::string LoginData = (std::string)username + (std::string)":" + std::to_string(hash(pass));
    name = (std::string)username;
    packetSend << LoginData;
    TCPSocket.send(packetSend);
    
    
    while (TCPSocket.receive(packetReceive) == sf::Socket::NotReady)
    {
        
    }
    
    int index = 0;
    
    packetReceive >> index;
    
    if (index == 255) {
        TCPSocket.disconnect();
        return false;
    }else {
        PlayerIndex = index;
        
        UDPSocket.setBlocking(false);
        
        unsigned short UDPPort = 8080;
        
        while (UDPSocket.bind(UDPPort) == sf::Socket::Status::Error)
        {
            UDPPort++;
        }
    }


    return true;
}

void NetWorkManager::SendGameInfoTCP(CoinInfo* info)
{
    sf::Packet packetSend;
    
    packetSend << PlayerIndex;
    packetSend << info->PosX;
    packetSend << info->PosY;
    packetSend << info->Rotation;
    
    TCPSocket.send(packetSend);
}

void NetWorkManager::SendPlayerInfoUDP(PlayerInfo *info)
{
    sf::Packet packetSend;
    int type = kTypeInformation_Player;
    
    packetSend << type;
    packetSend << PlayerIndex;
    packetSend << info->PosX;
    packetSend << info->PosY;
    packetSend << info->Rotation;
    packetSend << info->Points;
    
    UDPSocket.send(packetSend, IP, 8080);
}

void NetWorkManager::SendSpikeBoxInfoUDP(SpikeBoxInfo * info)
{
    sf::Packet packetSend;
    int type = kTypeInformation_SpikeBox;
    
    packetSend << type;
    packetSend << info->PosX;
    packetSend << info->PosY;
    packetSend << info->Rotation;
    
    UDPSocket.send(packetSend, IP, 8080);
}

void NetWorkManager::SendVictoryUDP()
{
    sf::Packet packetSend;
    
    packetSend << kTypeInformation_Victory;
    packetSend << PlayerIndex;
    packetSend << name;
    UDPSocket.send(packetSend, IP, 8080);
}

void NetWorkManager::ReceiveGameInfoUDP()
{
    sf::Packet packetReceive;
    sf::IpAddress localIP = IP;
    unsigned short port = 8080;
    
    float msgPlayer;
    float msgBox;
    
    while (UDPSocket.receive(packetReceive, localIP, port) != sf::Socket::NotReady)
    {
        int EnumInformation;
        packetReceive >> EnumInformation;
        int index = 0;
				int points = 0;
        
        switch (EnumInformation)
        {
            case kTypeInformation_Player:
                packetReceive >> index;
                packetReceive >> msgPlayer;
                Players[index].PosX = msgPlayer;
                packetReceive >> msgPlayer;
                Players[index].PosY = msgPlayer;
                packetReceive >> msgPlayer;
                Players[index].Rotation = msgPlayer;
                packetReceive >> points;
								Players[index].Points = points;

								if (PlayerIndex != index) {
									switch (index)
									{
									case 0:
										Scene::GetInstance()->SetInGameOtherUsersPointsPosXY(kUser_1, Players[index].PosX, Players[index].PosY, Players[index].Points);
										break;
									case 1:
										Scene::GetInstance()->SetInGameOtherUsersPointsPosXY(kUser_2, Players[index].PosX, Players[index].PosY, Players[index].Points);
										break;
									case 2:
										Scene::GetInstance()->SetInGameOtherUsersPointsPosXY(kUser_3, Players[index].PosX, Players[index].PosY, Players[index].Points);
										break;
									case 3:
										Scene::GetInstance()->SetInGameOtherUsersPointsPosXY(kUser_4, Players[index].PosX, Players[index].PosY, Players[index].Points);
										break;
									default:
										break;
									}
								}			

                break;
                
            case kTypeInformation_SpikeBox:
                packetReceive >> msgBox;
                SpikeBox.PosX = msgBox;
                packetReceive >> msgBox;
                SpikeBox.PosY = msgBox;
                packetReceive >> msgBox;
                SpikeBox.Rotation = msgBox;
                break;
                
            case kTypeInformation_Victory:
                packetReceive >> index;
                if (PlayerIndex == index) {
                    Scene::GetInstance()->SetGameOverWinnerName(name);
                    Scene::GetInstance()->SetScene(kSceneType_GameOverWin);
                }
                else {
                    Scene::GetInstance()->SetGameOverLoserName(name);
                    std::string winnerName;
                    packetReceive >> winnerName;
                    Scene::GetInstance()->SetGameOverWinnerName(winnerName);
                    Scene::GetInstance()->SetScene(kSceneType_GameOverLose);
                }
                
                break;
                
            default:
                break;
        }
        
    }
}

void NetWorkManager::Disconnect()
{
    sf::Packet packetSend;
    
    packetSend << PlayerIndex;
    TCPSocket.send(packetSend);
    
    UDPSocket.unbind();
    TCPSocket.disconnect();
}

bool NetWorkManager::ReceiveGameInfoTCP()
{
    sf::Packet packetReceive;
    float msg;
    
    while (TCPSocket.receive(packetReceive) != sf::Socket::NotReady)
    {
        int index = 0;
        
        packetReceive >> index;
        
        packetReceive >> msg;
        Coin.PosX = msg;
        
        packetReceive >> msg;
        Coin.PosY = msg;
        
        packetReceive >> msg;
        Coin.Rotation = msg;
        return true;
    }
    
    return false;
}

int NetWorkManager::GetPoints()
{
    return Points;
}

void NetWorkManager::SetPoints(int points)
{
    Points = points;
}

void NetWorkManager::AddPoints(int points)
{
    Points += points;
}

void NetWorkManager::SubtractPoints(int points)
{
    if (Points <= 3)
        Points = 0;
    else
        Points -= points;
}


