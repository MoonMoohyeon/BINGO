#include "MHMoonGame.h"

/*

모든 변수 및 함수 클래스에 포함될 것
프로젝트에 본인이름이니셜Game 클래스 존재할 것
실행 시 모든 화면에 학번이름 출력할 것
메뉴 만들어 운영할 것
빙고판의 크기는 동적할당 할 것
사용자와 컴퓨터의 선택은 서로 다른 문자로 출력할 것
승패 판단이 명확할 것
승패가 결정된 후 빙고판 상태를 출력할 것
윈도우 API를 통해 인터페이스를 개선할 것

컴퓨터 알고리즘 고안
저장하기 기능
리플레이 기능

createMap

inGameCursor
playerTurn
computerTurn
findBestPlay

decision

saveGame / loadGame
replay

*/

int main(void)
{
	MHMoonGame game;
	game.play();
	return 0;
}