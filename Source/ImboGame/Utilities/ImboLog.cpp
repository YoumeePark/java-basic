#include "ImboLog.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY(ImboGame);

void ImboLog::Log(int32 InValue)
{
	UE_LOG(ImboGame, Display, TEXT("%d"), InValue);
}

void ImboLog::Log(float InValue)
{
	UE_LOG(ImboGame, Display, TEXT("%f"), InValue);
}
void ImboLog::Log(const FString& InValue)
{
	UE_LOG(ImboGame, Display, TEXT("%s"), *InValue);
}

void ImboLog::Log(const FVector& InValue)
{
	UE_LOG(ImboGame, Display, TEXT("%s"), *(InValue.ToString()));
}

void ImboLog::Log(const FRotator& InValue)
{
	UE_LOG(ImboGame, Display, TEXT("%s"), *(InValue.ToString()));
}

void ImboLog::Log(const UObject* InValue)
{
	FString str;

	if (!!InValue)
		str.Append(InValue->GetName());
	str.Append(!!InValue ? " NOT NULL" : "NULL");
	
	UE_LOG(ImboGame, Display, TEXT("%s"), *str);
}

void ImboLog::Log(const FString& InFileName, const FString& InFuncName, int32 InLineNumber)
{
	int32 index = 0;
	int32 length = 0;
	FString newFileName("");
	
	InFileName.FindLastChar(TEXT('\\'), index); 
	length = InFileName.Len() - 1;
	newFileName = InFileName.Right(length - index); //우측부터 인덱스 갯수 만큼의 문자

	FString str;
	str.Append(newFileName);
	str.Append(", ");
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(ImboGame, Display, TEXT("%s"), *str);
}

void ImboLog::Print(int32 InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
}

void ImboLog::Print(float InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
}

void ImboLog::Print(const FString& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
}

void ImboLog::Print(const FVector& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void ImboLog::Print(const FRotator& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void ImboLog::Print(const UObject* InValue, int32 InKey, float InDuration, FColor InColor)
{
	FString str;

	if (!!InValue)
		str.Append(InValue->GetName());
	str.Append(!!InValue ? " NOT NULL" : "NULL");

	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, str);
}

void ImboLog::Print(const FString& InFileName, const FString& InFuncName, int32 InLineNumber)
{
	int32 index = 0;
	int32 length = 0;
	FString newFileName("");

	InFileName.FindLastChar(TEXT('\\'), index);
	length = InFileName.Len() - 1;
	newFileName = InFileName.Right(length - index); //우측부터 인덱스 갯수 만큼의 문자

	FString str;
	str.Append(newFileName);
	str.Append(", ");
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, str);
}
