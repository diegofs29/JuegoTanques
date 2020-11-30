#include "Space.h"

Space::Space() {
	dynamicActors.clear();
	staticActors.clear();
}

void Space::update() {
	for (auto const& actor : dynamicActors) {
		updateMoveRight(actor);
		updateMoveLeft(actor);
        updateMoveTop(actor);
        updateMoveDown(actor);
	}
}

void Space::updateMoveRight(Actor* dynamicAct) {
    if (dynamicAct->vx > 0) {
        float possibleMovement = dynamicAct->vx;

        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;

        for (auto const& staticAct : staticActors) {
            int leftStatic = staticAct->x - staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;

            if ((rightDynamic + dynamicAct->vx) >= leftStatic
                && rightDynamic <= leftStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                if (possibleMovement >= leftStatic - rightDynamic) {
                    possibleMovement = leftStatic - rightDynamic;
                }
            }
        }

        for (auto const& slowingAct : slowingActors) {
            int leftSlowing = slowingAct->x - slowingAct->width / 2;
            int topSlowing = slowingAct->y - slowingAct->height / 2;
            int downSlowing = slowingAct->y + slowingAct->height / 2;

            if (rightDynamic > leftSlowing && topDynamic < downSlowing && topSlowing < downDynamic) {
                possibleMovement /= 1.5;
                break;
            }
        }

        dynamicAct->realX += possibleMovement;
    }

}

void Space::updateMoveLeft(Actor* dynamicAct) {
    if (dynamicAct->vx < 0) {
        float possibleMovement = dynamicAct->vx;

        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;

        for (auto const& staticAct : staticActors) {
            int rightStatic = staticAct->x + staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;

            if ((leftDynamic + dynamicAct->vx) <= rightStatic
                && leftDynamic >= rightStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                if (possibleMovement <= rightStatic - leftDynamic) {
                    possibleMovement = rightStatic - leftDynamic;
                }

            }

        }
        for (auto const& slowingAct : slowingActors) {
            int rightSlowing = slowingAct->x + slowingAct->width / 2;
            int topSlowing = slowingAct->y - slowingAct->height / 2;
            int downSlowing = slowingAct->y + slowingAct->height / 2;

            if (leftDynamic > rightSlowing && topDynamic < downSlowing && topSlowing < downDynamic) {
                possibleMovement /= 1.5;
                break;
            }
        }

        dynamicAct->realX += possibleMovement;
    }
}

void Space::updateMoveDown(Actor* dynamicAct) {
    if (dynamicAct->vy > 0) {
        float possibleMovement = dynamicAct->vy;

        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;
        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

        for (auto const& staticAct : staticActors) {
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            if ((downDynamic + dynamicAct->vy) >= topStatic
                && topDynamic < downStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                if (possibleMovement >= topStatic - downDynamic) {
                    possibleMovement = topStatic - downDynamic;
                }
            }
        }
        for (auto const& slowingAct : slowingActors) {
            int leftSlowing = slowingAct->x - slowingAct->width / 2;
            int rightSlowing = slowingAct->x + slowingAct->width / 2;
            int topSlowing = slowingAct->y - slowingAct->height / 2;
            int downSlowing = slowingAct->y + slowingAct->height / 2;

            if (rightDynamic > leftSlowing && leftDynamic < rightSlowing && topDynamic < downSlowing && topSlowing < downDynamic) {
                possibleMovement /= 1.5;
                break;
            }
        }
        dynamicAct->realY += possibleMovement;
    }
}

void Space::updateMoveTop(Actor* dynamicAct) {
    if (dynamicAct->vy < 0) {
        float possibleMovement = dynamicAct->vy;

        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;
        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

        for (auto const& staticAct : staticActors) {
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            if ((topDynamic + dynamicAct->vy) <= downStatic
                && downDynamic > topStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                if (possibleMovement <= downStatic - topDynamic) {
                    possibleMovement = downStatic - topDynamic;
                }
            }
        }
        for (auto const& slowingAct : slowingActors) {
            int leftSlowing = slowingAct->x - slowingAct->width / 2;
            int rightSlowing = slowingAct->x + slowingAct->width / 2;
            int topSlowing = slowingAct->y - slowingAct->height / 2;
            int downSlowing = slowingAct->y + slowingAct->height / 2;

            if (rightDynamic > leftSlowing && leftDynamic < rightSlowing && topDynamic < downSlowing && topSlowing < downDynamic) {
                possibleMovement /= 1.5;
                break;
            }
        }
        dynamicAct->realY += possibleMovement;
    }
}

void Space::addDynamicActor(Actor* actor) {
	dynamicActors.push_back(actor);
}

void Space::addStaticActor(Actor* actor) {
	staticActors.push_back(actor);
}

void Space::addSlowingActor(Actor* actor) {
	slowingActors.push_back(actor);
}

void Space::removeDynamicActor(Actor* actor) {
	dynamicActors.remove(actor);
}

void Space::removeStaticActor(Actor* actor) {
	staticActors.remove(actor);
}

void Space::removeSlowingActor(Actor* actor) {
	slowingActors.remove(actor);
}