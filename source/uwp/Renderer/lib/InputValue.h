// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("BB1D1269-2243-4F34-B4EC-5216296EBBA0") InputValue
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveInputValue>
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* adaptiveInputElement,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* uiInputElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

        IFACEMETHODIMP get_InputElement(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputElement** inputElement);
        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) = 0;

        IFACEMETHODIMP Validate(_Out_ boolean* isInputValid);

    protected:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid);
        virtual HRESULT SetValidation(boolean isValid);

        virtual HRESULT EnableFocusLostValidation();
        virtual HRESULT EnableValueChangedValidation() = 0;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IBorder> m_validationBorder;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_validationError;
    };

    class TextInputBase : public InputValue
    {
    public:
        TextInputBase() : m_isTextChangedValidationEnabled(false) {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* adaptiveInputElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* uiTextBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    protected:
        virtual HRESULT EnableValueChangedValidation() override;

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ITextBox> m_textBoxElement;
        bool m_isTextChangedValidationEnabled;
    };

    class TextInputValue : public TextInputBase
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveTextInput* adaptiveTextInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* uiTextBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

    protected:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveTextInput> m_adaptiveTextInput;
    };

    class NumberInputValue : public TextInputBase
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveNumberInput* adaptiveNumberInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* uiTextBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

    protected:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveNumberInput> m_adaptiveNumberInput;
    };

    class DateInputValue : public InputValue
    {
    public:
        DateInputValue() : m_isDateChangedValidationEnabled(false) {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveDateInput* adaptiveDateInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ICalendarDatePicker* uiDatePickerElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    protected:
        virtual HRESULT EnableValueChangedValidation() override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveDateInput> m_adaptiveDateInput;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ICalendarDatePicker> m_datePickerElement;
        bool m_isDateChangedValidationEnabled;
    };

    class TimeInputValue : public InputValue
    {
    public:
        TimeInputValue() : m_isTimeChangedValidationEnabled(false) {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveTimeInput* adaptiveTimeInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITimePicker* uiTimePickerElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    protected:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;
        virtual HRESULT EnableValueChangedValidation() override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveTimeInput> m_adaptiveTimeInput;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ITimePicker> m_timePickerElement;
        bool m_isTimeChangedValidationEnabled;
    };

    class ToggleInputValue : public InputValue
    {
    public:
        ToggleInputValue() : m_isToggleChangedValidationEnabled(false) {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveToggleInput* adaptiveTimeInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ICheckBox* uiCheckBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    protected:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;
        virtual HRESULT EnableValueChangedValidation() override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveToggleInput> m_adaptiveToggleInput;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ICheckBox> m_checkBoxElement;
        bool m_isToggleChangedValidationEnabled;
    };

    class ChoiceSetInputValue : public InputValue
    {
    public:
        ChoiceSetInputValue() : m_isChoiceSetChangedValidationEnabled(false) {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* uiChoiceSetElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* validationError);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    protected:
        virtual HRESULT EnableValueChangedValidation() override;
        virtual HRESULT EnableFocusLostValidation() override;

    private:
        std::string GetChoiceValue(_In_ ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex) const;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput> m_adaptiveChoiceSetInput;
        bool m_isChoiceSetChangedValidationEnabled;
    };
}
