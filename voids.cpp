//#
//include"voids.h"
//
//void Boids::initBoids()
//{
//    for (int i = 0; i < numBoids; i += 1) {
//        boids[boids.begin()] = {
//          pos.x = rand() * width,
//          pos.y = rand() * height,
//          dx : Math.random() * 10 - 5,
//          dy : Math.random() * 10 - 5,
//          history : [] ,
//        };
//    }
//}
//
//void Boids::distance(Boids a, Boids b)
//{
//    return Math.sqrt(//�������o���Ă�
//        (a.x - b.x) * (.x - b.x) +
//        (a.y - b.y) * (a.y - b.y),
//        );
//}
//
//void Boids::nClosestBoids(Boids n)
//{
//    return Math.sqrt(//�Εӂ��o���Ă�
//        (boid1.x - boid2.x) * (boid1.x - boid2.x) +
//        (boid1.y - boid2.y) * (boid1.y - boid2.y),
//        );
//}
//
//void Boids::sizeCanvas()
//{
//    // Make a copy
//    const sorted = boids.slice();//�R�s�[������Ă�炵���@�؂���֐�
//    // Sort the copy by distance from `boid`
//    sorted.sort((a, b) = > distance(boid, a) - distance(boid, b));//�ׂƔ�ׂ�
//    // Return the `n` closest
//    return sorted.slice(1, n + 1);//�����ꂽ���܂ŏ��Ԃɏ��������ɕ��ׂ�
//}
//
//void Boids::keepWithBounds(Boids)
//{
//}
//
//void Boids::avoidOthers(Boids)
//{
//}
//
//void Boids::mathVelocity(Boids)
//{
//}
//
//void Boids::drawBoids(Boids boid)
//{
//}
//
//void Boids::animationLoop()
//{
//}
