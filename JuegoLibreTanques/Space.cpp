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

        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;

        for (auto const& staticAct : staticActors) {
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            if ((rightDynamic + dynamicAct->vx) >= leftStatic
                && rightDynamic <= leftStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                if (possibleMovement >= leftStatic - rightDynamic) {
                    possibleMovement = leftStatic - rightDynamic;
                    dynamicAct->vx = possibleMovement;  // Solo es necesario si se choca, en el resto de casos no
                }
            }
        }

        for (auto const& dynAct : dynamicActors) {
            int topDyn = dynAct->y - dynAct->height / 2;
            int downDyn = dynAct->y + dynAct->height / 2;
            int leftDyn = dynAct->x - dynAct->width / 2;

            if ((rightDynamic + dynamicAct->vx) >= leftDyn + dynAct->vx
                && rightDynamic <= leftDyn
                && topDyn < downDynamic
                && downDyn > topDynamic) {

                if (possibleMovement >= leftDyn - rightDynamic) {
                    possibleMovement = leftDyn - rightDynamic;
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

        dynamicAct->realX += possibleMovement;
    }

}

void Space::updateMoveLeft(Actor* dynamicAct) {
    if (dynamicAct->vx < 0) {
        float possibleMovement = dynamicAct->vx;

        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;

        for (auto const& staticAct : staticActors) {
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;

            if ((leftDynamic + dynamicAct->vx) <= rightStatic
                && leftDynamic >= rightStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                if (possibleMovement <= rightStatic - leftDynamic) {
                    possibleMovement = rightStatic - leftDynamic;
                    dynamicAct->vx = possibleMovement;
                }

            }

        }

        for (auto const& dynAct : dynamicActors) {
            int topDyn = dynAct->y - dynAct->height / 2;
            int downDyn = dynAct->y + dynAct->height / 2;
            int rightDyn = dynAct->x + dynAct->width / 2;

            if ((leftDynamic + dynamicAct->vx) <= rightDyn + dynAct->vx
                && leftDynamic >= rightDyn
                && topDyn < downDynamic
                && downDyn > topDynamic) {

                if (possibleMovement <= rightDyn - leftDynamic) {
                    possibleMovement = rightDyn - leftDynamic;
                    cout << possibleMovement << endl;
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
                    dynamicAct->vy = possibleMovement;
                }
            }
        }

        for (auto const& dynAct : dynamicActors) {
            int topDyn = dynAct->y - dynAct->height / 2;
            int rightDyn = dynAct->x + dynAct->width / 2;
            int leftDyn = dynAct->x - dynAct->width / 2;

            if ((downDynamic + dynamicAct->vy) >= topDyn + dynAct->vy
                && downDynamic <= topDyn
                && leftDynamic < rightDyn
                && rightDynamic > leftDyn) {

                if (possibleMovement >= topDyn - downDynamic) {
                    possibleMovement = topDyn - downDynamic;
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
                    dynamicAct->vy = possibleMovement;
                }
            }
        }

        for (auto const& dynAct : dynamicActors) {
            int downDyn = dynAct->y + dynAct->height / 2;
            int rightDyn = dynAct->x + dynAct->width / 2;
            int leftDyn = dynAct->x - dynAct->width / 2;

            if ((topDynamic + dynamicAct->vy) <= downDyn + dynAct->vy
                && topDynamic >= downDyn
                && leftDynamic < rightDyn
                && rightDynamic > leftDyn) {

                if (possibleMovement <= downDyn - topDynamic) {
                    possibleMovement = downDyn - topDynamic;
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