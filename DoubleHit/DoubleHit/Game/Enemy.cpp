

#include "Enemy.h"
#include "Mode1.h"
#include "Bullet.h"
#include "Skill.h"
#include "Floor.h"
#include "HealthBar.h"
#include <cmath>
#define E_attack_time rand()%6 + 9


Enemy::Enemy(Math::vec2 start_position) :
    GameObject(start_position)
{
    SetScale({ 1,1 });
}

Math::vec2 Enemy::Normalize(const Math::vec2& vec) {
    length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length == 0) {return vec;}

    
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;

    return normalized_vec;
}

//###############################################################################################################################################################################################################

GroundEnemy::GroundEnemy(Math::vec2 start_position ):
    Enemy(start_position)
{
    distance = 600;
    CS230::GameObject::AddGOComponent(new CS230::Sprite("Assets/enemy/robot.spt", this));
    SetScale({1,1});
    attack_timer = new CS230::Timer(attack_time);
    AddGOComponent(attack_timer);
}

void GroundEnemy::Update(double dt)
{
    GameObject::Update(dt);
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    if (hero->GetOnEliteGround()) {
        Destroy();
    }
    if (attack) {
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new GEnemyAttack(this));
        attack = false;
        attackExecuted = true;
    }
    if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Die)) {
        if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
            Destroy();
            if (hero != nullptr) {
                hero->AddExp(150);
                Engine::GetLogger().LogEvent("Add Exp 150 ");

            }
            Engine::GetLogger().LogEvent("Add Score 300 ");
            Engine::GetGameStateManager().GetGSComponent<CS230::Score>()->Add(300);
        }
    }
    else {
        x_distance = hero->GetPosition().x - GetPosition().x;
        direction = Math::vec2(x_distance, 0.0);    //no direction in y
        distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance

        if (distance > min_distance) {  //collision
            if (!has_run) {
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
                has_run = true;
            }
            SetVelocity({ Normalize(direction).x * speed , Normalize(direction).y * speed });
            if (GetVelocity().x < 0) {
                SetScale({ 1,1 });
            }
            else if (GetVelocity().x >= 0) {
                SetScale({ -1,1 });
            }
        }
        else if (distance <= min_distance) {
            SetVelocity({ 0,0 });
            if (has_run) {
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
                has_run = false;
            }
        }
        if (distance <= shooting_range) {
            if (attack_timer->Remaining() == 0.0) {
                attack_timer->Set(attack_time);
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack)); 
                attackExecuted = false;
            }
            else if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
                if (GetGOComponent<CS230::Sprite>()->GetCurrentFrame() == 13 && !attackExecuted) {
                    attack = true;
                }
                else if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
                    has_run = false;
                }
            }
        }
    }
}

bool GroundEnemy::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Bullet:
    case GameObjectTypes::BulletHeavy:
    case GameObjectTypes::HeroLight:
    case GameObjectTypes::HeroHeavy:
        return true;
        break;
    }
    return false;
}

void GroundEnemy::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Bullet:
        health -= Bullet::GetDamage() / 2;
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::BulletHeavy:
        health -= BulletHeavy::GetDamage();
        if (health < 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroLight:
        health -= Hero_Light::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroHeavy:
        health -= Hero_Heavy::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::UpgradeLL:
        Engine::GetLogger().LogDebug("Detected");
        health -= Hero_Light_Light::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    }

}


//###############################################################################################################################################################################################################

AirEnemy::AirEnemy(Math::vec2 start_position) :
    Enemy(start_position)
{
    distance = 600;
    AddGOComponent(new CS230::Sprite("Assets/enemy/flying_robot.spt", this));
    SetScale({ 1,1 });
    attack_timer = new CS230::Timer(0.0);
    AddGOComponent(attack_timer);
}

void AirEnemy::Update(double dt)
{
    GameObject::Update(dt);
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    if (hero->GetOnEliteGround()) {
        Destroy();
    }

    if (attack) {
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new AEnemyBullet(GetPosition(), { hero->GetPosition() }));
        attack = false;
        attackExecuted = true;
    }
    if (!has_run) {
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
        has_run = true;
    }
    else if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Die)) {
        if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
            Destroy();
            if (hero != nullptr) {
                hero->AddExp(150);
                Engine::GetLogger().LogEvent("Add Exp 150");
            }

            Engine::GetLogger().LogEvent("Add Score 200 ");
            Engine::GetGameStateManager().GetGSComponent<CS230::Score>()->Add(200);
        }
        //else if (GetGOComponent<CS230::Collision>() == nullptr) {
        //    Destroy();
        //}
    }
    else {
        direction = const_cast<Math::vec2&>(hero->GetPosition()) - GetPosition();
        distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));     //calculate distance
        
        if (distance <= min_distance || GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
            SetVelocity({ 0,0 });
            if (GetGOComponent<CS230::Sprite>()->GetCurrentFrame() == 11 && !attackExecuted) {
                attack = true;
            }
        }
        else if (distance > min_distance) {  //collision
            SetVelocity({ Normalize(direction).x * speed , Normalize(direction).y * speed });
            
            if (GetVelocity().x < 0) {
                SetScale({ 1,1 });
            }
            else if (GetVelocity().x >= 0) {
                SetScale({ -1,1 });
            }
        }
        if (distance < shooting_range) {
            if (attack_timer->Remaining() == 0.0) {
                attack_timer->Set(attack_time);
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
                attackExecuted = false;
            }
            else if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
                if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
                    has_run = false;
                }
            }
        }
    }
}

bool AirEnemy::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Bullet:
    case GameObjectTypes::BulletHeavy:
    case GameObjectTypes::HeroLight:
        return true;
        break;
    }
    return false;
}

void AirEnemy::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Bullet:
        health -= Bullet::GetDamage();
        if (health < 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::BulletHeavy:
        health -= BulletHeavy::GetDamage();
        if (health < 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroLight:
        health -= Hero_Light::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroHeavy:
        health -= Hero_Heavy::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::UpgradeLL:
        Engine::GetLogger().LogDebug("Detected");
        health -= Hero_Light_Light::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::UpgradeLH:
        health -= Hero_Light_Heavy::GetDamage(); //should be run only once
        
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    }
}



//###############################################################################################################################################################################################################

EliteEnemy::EliteEnemy(Math::vec2 start_position):
    Enemy(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/enemy/elite_enemy.spt", this));

    SetHealth(max_health);
    idle_timer = new CS230::Timer(idle_time);
    attack_timer = new CS230::Timer(E_attack_time);
    AddGOComponent(idle_timer);
    AddGOComponent(attack_timer);
    current_state = &state_waiting;
    current_state->Enter(this);
}

void EliteEnemy::Update(double dt)
{
    GameObject::Update(dt);


}


void EliteEnemy::State_Wating::Enter(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    //enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
    //enemy->SetVelocity({ hero->GetVelocity().x, Hero::velocity.y });
}
void EliteEnemy::State_Wating::Update(GameObject* object, double dt)
{


}
void EliteEnemy::State_Wating::CheckExit(GameObject* object)
{
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    if (hero->GetOnEliteGround()) {
        Engine::GetGameStateManager().GetGSComponent<EliteHealthBar>()->Add("Assets/UI/elite_health_back.png", { 220, (double)Engine::GetWindow().GetSize().y - 88 }, 2.0);
        Engine::GetGameStateManager().GetGSComponent<EliteHealthBar>()->Add("Assets/UI/elite_health_middle.png", { 288, (double)Engine::GetWindow().GetSize().y - 88 }, 2.0, enemy, max_health);
        Engine::GetGameStateManager().GetGSComponent<EliteHealthBar>()->Add("Assets/UI/elite_health_top.png", { 220, (double)Engine::GetWindow().GetSize().y - 88 }, 2.0);
        enemy->attack_timer->Set(E_attack_time);
        enemy->change_state(&enemy->state_idle);
    }
}


void EliteEnemy::State_Idle::Enter(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    enemy->idle_timer->Set(idle_time);
    enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
    //enemy->SetVelocity({ hero->GetVelocity().x, Hero::velocity.y });
}

void EliteEnemy::State_Idle::Update(GameObject* object, double dt)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    if (enemy->attack_timer->Remaining() == 0.0 && !enemy->has_run) {
        enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Teleport));
        enemy->has_run = true;
    }
}

void EliteEnemy::State_Idle::CheckExit(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    if (enemy->idle_timer->Remaining() == 0.0 && enemy->GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Idle)) {
        enemy->change_state(&enemy->state_running);
    }  

    if (enemy->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        
        enemy->change_state(&enemy->state_attacking);
    }
    
}


void EliteEnemy::State_Running::Enter(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}

void EliteEnemy::State_Running::Update(GameObject* object, double dt)
{
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    enemy->distance = (hero->GetPosition().x) - enemy->GetPosition().x;

    if (enemy->attack_timer->Remaining() == 0.0 && !enemy->has_run) {
        enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Teleport));
        enemy->has_run = true;
    }
    if (enemy->distance > 0) { 
        enemy->SetScale({ 1,1 });
        enemy->SetVelocity({ speed ,enemy->GetVelocity().y });
    }
    else if (enemy->distance == 0) {
        enemy->SetVelocity({ 0, 0});
    }
    else {
        enemy->SetScale({ -1,1 });
        enemy->SetVelocity({ -speed ,enemy->GetVelocity().y });
    }

}

void EliteEnemy::State_Running::CheckExit(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    if (abs(enemy->distance) <= min_distance && enemy->GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Idle)) {
            enemy->change_state(&enemy->state_punching);
    }
    if (enemy->GetGOComponent<CS230::Sprite>()->AnimationEnded())
        enemy->change_state(&enemy->state_attacking);
}


void EliteEnemy::State_Punching::Enter(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Punch));
    enemy->SetVelocity({ 0,0 });
}

void EliteEnemy::State_Punching::Update(GameObject* object, double dt)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    CS230::Sprite* sprite = enemy->GetGOComponent<CS230::Sprite>();
    if (sprite->GetCurrentFrame() == 29 && !enemy->attack) {
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyLight(enemy));
        enemy->attack = true;
    }
}

void EliteEnemy::State_Punching::CheckExit(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    if (enemy->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        enemy->attack = false;
        enemy->change_state(&enemy->state_idle);
    }
}

void EliteEnemy::State_Attacking::Enter(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    EliteFloor* floor = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteFloor>();
    enemy->SetVelocity({ 0,0 });
    if (rand() % 2 == 1) {
        enemy->SetPosition({ (double)floor->GetBoundary().Left(),enemy->GetPosition().y});
        if (enemy->GetScale().x < 0) {
            enemy->SetScale({ 1,1 });
        }
    }
    else {
        enemy->SetPosition({ (double)floor->GetBoundary().Right(),enemy->GetPosition().y });
        if (enemy->GetScale().x > 0) {
            enemy->SetScale({ -1,1 });
        }
    }
    enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Teleport2));

}

void EliteEnemy::State_Attacking::Update(GameObject* object, double dt)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    EliteFloor* floor = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteFloor>();
    CS230::Sprite* sprite = enemy->GetGOComponent<CS230::Sprite>();


    if (sprite->AnimationEnded()) {
        sprite->PlayAnimation(static_cast<int>(Animations::Attack));
        enemy->pos = { (double)floor->GetBoundary().Left() + rand() % 100 + 50, (double)floor->GetBoundary().Top() };
        enemy->pos2 = { (double)floor->GetBoundary().Left() + rand() % 100 + 150, (double)floor->GetBoundary().Top() };
        enemy->pos3 = { (double)floor->GetBoundary().Left() + rand() % 100 + 250, (double)floor->GetBoundary().Top() };
        enemy->pos4 = { (double)floor->GetBoundary().Left() + rand() % 100 + 350, (double)floor->GetBoundary().Top() };
        enemy->pos5 = { (double)floor->GetBoundary().Left() + rand() % 100 + 550, (double)floor->GetBoundary().Top() };
         Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttackAlert(enemy->pos));
         Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttackAlert(enemy->pos2));
         Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttackAlert(enemy->pos3));
         Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttackAlert(enemy->pos4));
         Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttackAlert(enemy->pos5));
    }
    if (sprite->GetCurrentFrame()== 20 && !enemy->attack) {

        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttack(enemy->pos));
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttack(enemy->pos2));
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttack(enemy->pos3));
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttack(enemy->pos4));
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EEnemyAttack(enemy->pos5));
        enemy->attack = true;
    }
}

void EliteEnemy::State_Attacking::CheckExit(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    if (enemy->GetGOComponent<CS230::Sprite>()->AnimationEnded() && enemy->GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
        enemy->attack_timer->Set(E_attack_time);
        enemy->has_run = false;
        enemy->attack = false;
        enemy->change_state(&enemy->state_idle);
    }

}

void EliteEnemy::State_Storming::Enter(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);
    enemy->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Punch));
    enemy->SetVelocity({ 0,0 });
}

void EliteEnemy::State_Storming::Update(GameObject* object, double dt)
{
}

void EliteEnemy::State_Storming::CheckExit(GameObject* object)
{
    EliteEnemy* enemy = static_cast<EliteEnemy*>(object);

}

bool EliteEnemy::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::BulletHeavy:
    case GameObjectTypes::HeroLight:
    case GameObjectTypes::HeroHeavy:
    case GameObjectTypes::UpgradeLL:
        return true;
        break;
    }
    return false;
}

void EliteEnemy::ResolveCollision(GameObject* other_object)
{
    if (GetHealth() <= 0) {
        RemoveGOComponent<CS230::Collision>();
        SetVelocity({ 0,0 });
        Engine::GetGameStateManager().GetGSComponent<EliteHealthBar>()->Unload();
        Destroy();
    }
    switch (other_object->Type()) {
    //case GameObjectTypes::Bullet:
    //    SetHealth(GetHealth() - Bullet::GetDamage() / demerit);
    //    break;
    case GameObjectTypes::BulletHeavy:
        SetHealth(GetHealth() - 0.2);
        break;
    case GameObjectTypes::HeroLight:
        SetHealth(GetHealth() - Hero_Light::GetDamage() / demerit);
        break;
    case GameObjectTypes::HeroHeavy:
        SetHealth(GetHealth() - Hero_Heavy::GetDamage());
        break;
    case GameObjectTypes::UpgradeLL:
        SetHealth(GetHealth() - Hero_Light_Light::GetDamage());
        break;
    }
}