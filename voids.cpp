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
//    return Math.sqrt(//距離を出してる
//        (a.x - b.x) * (.x - b.x) +
//        (a.y - b.y) * (a.y - b.y),
//        );
//}
//
//void Boids::nClosestBoids(Boids n)
//{
//    return Math.sqrt(//斜辺を出してる
//        (boid1.x - boid2.x) * (boid1.x - boid2.x) +
//        (boid1.y - boid2.y) * (boid1.y - boid2.y),
//        );
//}
//
//void Boids::sizeCanvas()
//{
//    // Make a copy
//    const sorted = boids.slice();//コピーを作ってるらしい　切り取り関数
//    // Sort the copy by distance from `boid`
//    sorted.sort((a, b) = > distance(boid, a) - distance(boid, b));//隣と比べて
//    // Return the `n` closest
//    return sorted.slice(1, n + 1);//入れられたｎまで順番に小さい順に並べる
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
