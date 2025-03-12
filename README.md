![image](https://github.com/minhvvan/Splendor/assets/59609086/b54009a9-3ca6-48ce-b696-ed63af5001db)

# Splendor
<table>
<tr>
<td>
  Splendor Board Game
  
  2인 Multiplayer(Using Steam) 
</td>
</tr>
</table>



## Architecture
![Struct](https://github.com/minhvvan/Splendor/assets/59609086/743e0d95-7c0d-4816-a742-6584930df4bb)




## Demo
1. Launch Steam App
2. execute /BuildGame/Splendor/Splendor.exe
3. Make the Match(Host & Join Session)
4. Game Start



## Rule
1. 선택 액션(행동해도 턴이 넘어가지 않음):
  - 특권 1개 사용: 황금 토큰을 제외한 토큰 1개를 가져옴
  - 토큰 채우기: 보드에 사용한 토큰들을 채움(상대가 특권 1개를 가져감)
2. 필수 액션:
  - 가로나 세로, 대각선으로 한 줄로 이어진 토큰 최대 3개 가져오기
    - 황금 토큰 가져오기(카드 하나를 선택해 손으로 가져옴 최대 3개까지 가능)
    - 같은 색깔 3개나 진주 2개를 가져오면 상대는 특권을 1개 얻음
  - 열려있는 카드나 손에 있는 카드를 구매함
    - 자신이 가진 보너스만큼 비용을 적게 지불
3. 아이템:

  | Before        | After         |
  | ------------- | ------------- |
  |<img src = "https://github.com/minhvvan/Splendor/assets/59609086/210e9882-89a9-4495-bfba-518650e1de20" width="30" height="30"> | 차례가 끝난 뒤, 추가 차례 한 번 진행 |
  |<img src = "https://github.com/minhvvan/Splendor/assets/59609086/39c89933-e981-41d9-8485-896112b80d32" width="30" height="30"> | 특권 1개 가져옴 |
  |<img src = "https://github.com/minhvvan/Splendor/assets/59609086/1c423397-7abf-4192-923f-62be6cf0257d" width="30" height="30"> | 게임판에서 색깔이 동일한 토큰 1개를 가져옴 |
  |<img src = "https://github.com/minhvvan/Splendor/assets/59609086/a53af04f-67ed-404f-99af-83e8e0586e9a" width="30" height="30"> | 상대에게서 황금 토큰을 제외한 토큰 1개를 가져옴 |
  |<img src = "https://github.com/minhvvan/Splendor/assets/59609086/1906ac06-3b56-464f-80f8-390cfe01391e" width="30" height="30"> | 내가 이미 갖고 있는 보너스 색깔 중 하나를 복 |
4. 왕관을 3개째 / 6개째 모을 시: 왕족 카드 1장 가져옴
5. 차례 종료 시 토큰을 10개까지만 남기고 버림
6. 게임 종료 조건
  - 승점 20점
  - 완관 10개
  - 한 색깔의 카드들로 승점 10점


## Preview

### Lobby
#### Host Game
![HostGame](https://github.com/minhvvan/Splendor/assets/59609086/41dc8bec-2bdc-4f7d-8892-f6ffa25eab8b)

#### Join Game
![JoinGame](https://github.com/minhvvan/Splendor/assets/59609086/aa6876ce-d25f-4638-979b-1dd4dc09641c)



### Game
#### Select Token
![SelecetToken](https://github.com/minhvvan/SteamTest/assets/59609086/c28b879d-78fe-42eb-bfb4-1b62844259e5)

#### Over Token
![overToken](https://github.com/minhvvan/SteamTest/assets/59609086/2f211923-b161-4912-a39e-f312d08aed9d)

#### Fill Token
![FillToken](https://github.com/minhvvan/SteamTest/assets/59609086/b476f9b9-2bd3-4c53-8521-457d46be19bb)

#### Gold Token
![GoldToken](https://github.com/minhvvan/SteamTest/assets/59609086/cbc88ce5-f0df-4caf-86c1-852ddf9931ca)



### Item
#### Get Token
![GetToken](https://github.com/minhvvan/SteamTest/assets/59609086/e4fa95c7-18df-4523-afe4-a786798f9f9b)

#### Get Scroll
![GetScroll](https://github.com/minhvvan/SteamTest/assets/59609086/4dddc4a7-3f32-4a90-8c6a-278834abb5f2)

#### Replay
![Replay](https://github.com/minhvvan/SteamTest/assets/59609086/3c965c3f-6272-4571-a50f-e75b4ae28e3d)

#### Take Token
![TakeToken](https://github.com/minhvvan/SteamTest/assets/59609086/ab9bbb98-ef80-4eec-a7fa-882129151a77)

#### Any Color
![AnyColor](https://github.com/minhvvan/SteamTest/assets/59609086/7ab7cc0f-57e8-48e0-b1cb-792998a021d7)



### Crown
#### Add Crown
![GetCrown](https://github.com/minhvvan/SteamTest/assets/59609086/cb16f96c-6e31-428c-a79a-d643db0ba787)

#### Crown Event
![CrownEvent](https://github.com/minhvvan/Splendor/assets/59609086/8435cc53-60d6-4a99-8422-05d932615d9a)



### Util
### Check Rival Info
![Tab](https://github.com/minhvvan/Splendor/assets/59609086/16fb76ea-f208-4c63-9e1b-e2278848adb8)




## Performance

- 어두운 배경에 핀조명같은 연출을 위해 spotLight 두 개를 교차하게 배치하였지만 라이팅 복잡도 증가
- 제거하여도 게임 내 화면에 변화가 크지 않아 제거

| Before        | After         |
| ------------- | ------------- |
| ![Splendor - 언리얼 에디터 2023-12-05 오후 1_47_43](https://github.com/minhvvan/Splendor/assets/59609086/c28a47bf-465a-4b25-a980-f9a07f644910) | ![Splendor - 언리얼 에디터 2023-12-05 오후 1_48_03](https://github.com/minhvvan/Splendor/assets/59609086/8d694dc7-6538-4c54-bef9-6d56ad38081f) |
|  ![Splendor (64 비트, Development PCD3D_SM6)  2023-12-05 오후 1_51_09](https://github.com/minhvvan/Splendor/assets/59609086/8626d445-44ec-4779-9104-720c7e86929f) | ![Splendor (64 비트, Development PCD3D_SM6)  2023-12-05 오후 1_52_12](https://github.com/minhvvan/Splendor/assets/59609086/de0c581d-ce84-465a-bb31-9d962a8c476f)  |
| <img width="503" alt="image" src="https://github.com/minhvvan/Splendor/assets/59609086/581a5734-0f11-459c-9cb1-03a69caffe44"> | <img width="503" alt="image" src="https://github.com/minhvvan/Splendor/assets/59609086/120aad51-7077-4792-8845-9ba349c68e67"> |




## Bug / Feature Request

- Card Cost 가시성 업데이트

| Before        | After         |
| ------------- | ------------- |
|<img width="351" alt="image" src="https://github.com/minhvvan/Splendor/assets/59609086/edb3144c-bf58-4bce-b135-b92fb2a09fda"> | <img width="344" alt="image" src="https://github.com/minhvvan/Splendor/assets/59609086/49ccdb99-3521-481a-9d89-1e2818ebeadc"> |



