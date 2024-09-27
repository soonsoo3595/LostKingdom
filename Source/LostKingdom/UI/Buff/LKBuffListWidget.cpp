// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Buff/LKBuffListWidget.h"
#include "UI/Buff/LKBuffWidget.h"
#include "Character/LKCharacterBase.h"
#include "Components/HorizontalBox.h"

void ULKBuffListWidget::AddBuff(ULKBaseBuff* Buff)
{
	ULKBuffWidget** BuffWidget = BuffWidgets.Find(Buff);
	if(BuffWidget)
	{
		(*BuffWidget)->UpdateTime();
		return;
	}
	else
	{
		ULKBuffWidget* NewBuffWidget = CreateWidget<ULKBuffWidget>(this, BuffWidgetClass);
		if (NewBuffWidget)
		{
			NewBuffWidget->SetBuffWidget(Buff);
			BuffWidgets.Add(Buff, NewBuffWidget);
			BuffList->AddChild(NewBuffWidget);
		}
	}
}

void ULKBuffListWidget::RemoveBuff(ULKBaseBuff* Buff)
{
	ULKBuffWidget** BuffWidget = BuffWidgets.Find(Buff);
	if(BuffWidget)
	{
		BuffList->RemoveChild(*BuffWidget);
		BuffWidgets.Remove(Buff);
	}
}

void ULKBuffListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ALKCharacterBase* Character = Cast<ALKCharacterBase>(Owner);
	if(Character)
	{
		Character->OnBuffAdded.AddUObject(this, &ULKBuffListWidget::AddBuff);
		Character->OnBuffRemoved.AddUObject(this, &ULKBuffListWidget::RemoveBuff);
	}
}
